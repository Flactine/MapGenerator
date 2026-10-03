// ============================================================================
// MapGenMapFile.cpp - the ".map" writer
//
// The vanilla RMG itself never writes a file (the game saves the finished map
// through its own writer). The format was taken from three authoritative
// sources and checked byte for byte against a real shipped map,
// d:\Ra2\all01umd.map (a FinalAlert 2 saved mission map):
//
//   - the engine's own save path: MapClass's writer (sub_4AD7E0 @ 0x4AD7E0)
//     and the IsoMapPack5 builder (sub_56B3F0 @ 0x56B3F0), which packs each
//     cell as 11 bytes taken from +0x24, the dword at +0x38, +0x11A, +0x11B
//     and +0x119, and sets the pack up with sub_55C2B0(0, 0x2000) - 8192-byte
//     sections;
//   - Westwood's editor source, CNC_TS_and_RA2_Mission_Editor: MapData.cpp
//     (the sections, the 11-byte MAPFIELDDATA record, the 70-character
//     numbered-key layout of sub_526E80) and 3rdParty/xcc/misc/shp_decode.cpp
//     (encode5/encode5s = format 5, encode80 = format 80, encode64);
//   - all01umd.map, which shows the real bytes: [IsoMapPack5] starts with the
//     section header 2A 01 52 02 = {size_in 298, size_out 594}, i.e. a
//     compressed (LZO1X) 594-byte payload; [OverlayPack]/[OverlayDataPack] are
//     352 bytes = 32 sections of [3-byte little-endian length][0x20][format 80
//     payload], each payload of the shipped file ending in the stop byte 0x80;
//     all three sections use numbered keys of 70 characters.
//
// Two formats feed those packs:
//
//   format 5 (IsoMapPack5) is LZO1X. The port now runs the real LZO1X-1
//   encoder - a faithful port of LZO 2.03's lzo1x_1.c / lzo1x_c.c, the same
//   code minilzo ships as lzo1x_1_compress and what FinalAlert2 uses for this
//   pack - so the payload is a standard LZO1X stream ending in the end marker
//   0x11 0x00 0x00. An earlier port emitted only the uncompressed literal-run
//   form (control byte n - 3, or 0 followed by 255-chunks of n - 18, then the
//   marker): legal for the decoder, but it left the pack at its full size.
//
//   format 80 (OverlayPack / OverlayDataPack) is: 0x80 | n literal runs with
//   n <= 63 (XCC's write80_c1), then a bare 0x80 stop byte. Its section header
//   is the 3-byte packed length, a 0x20 byte, then the payload (EncodeF80).
//
// The 11-byte cell record (every field verified against both the engine's
// writer and the editor's MAPFIELDDATA):
//
//   +0  int16  X                cell +0x24   (MapCell::MapCoords low half)
//   +2  int16  Y                cell +0x26   (high half)
//   +4  uint16 IsoTileTypeIndex cell +0x38
//   +6  uint16 bMapData         cell +0x3A   (the tile dword's high half = 0)
//   +8  uint8  bSubTile         cell +0x11A  (the TMP slice the radar reads)
//   +9  uint8  bHeight          cell +0x11B  (the height cell +0x11B)
//   +10 uint8  bMapData2        cell +0x119
//
// A cell the RMG never tiled keeps the port's placeholder (0). The file gets
// the engine's own "no tile" sentinel 0xFFFF instead - see the note in the
// record loop - because 0 is a valid tile index to the game.
//
// Port mapping: bSubTile takes MapCell::Height (the TMP Z slice - exactly what
// CellClass::GetRadarColor reads at +0x11A) and bHeight takes MapCell::Level.
//
// The overlay grids are 262144 bytes (= 512 x 512), indexed X + 512 * Y - the
// same indexing the port's own cellSlots_ uses (CellAt: x + (y << 9)) and the
// one the editor writes (its m_Overlay[y + x * 512] with its X/Y swapped at the
// file boundary). 0xFF means "no overlay" (all01umd's whole grid is 0xFF).
//
// The text sections carry only what the generator produced. Scenario
// scaffolding the RMG has no counterpart for (triggers, teams, AI, houses) is
// deliberately absent; [Basic] uses the editor's own default template
// (data/FinalAlert2/StdMapRA2.ini) for the keys it needs.
//
// SaveMapFile also writes "<the map>.isopack5.txt": the same 11-byte records in
// readable form (one line per cell: coordinates, tile, the two height bytes,
// the port's own Height / Level / SlopeIndex / LandType / Passability and the
// raw bytes in hex). The .map itself cannot be eyeballed - its packs are base64
// of packed streams - so this is the file to diff against a reference.
// ============================================================================

#include "pch.h"
#include "MapGen.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <string>
#include <vector>

namespace {

// ---- byte helpers ---------------------------------------------------------

void PutU16(std::vector<uint8_t>& v, unsigned value)
{
    v.push_back(static_cast<uint8_t>(value & 0xFF));
    v.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
}

void PutU24(std::vector<uint8_t>& v, unsigned value)
{
    v.push_back(static_cast<uint8_t>(value & 0xFF));
    v.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    v.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
}

// ---- format 5: one IsoMapPack5 section (see the file header) --------------
//
// The pack is a real LZO1X-1 stream. These macros, Lzo1xDoCompress and
// Lzo1xCompress are a faithful port of LZO 2.03's src/lzo1x_1.c and
// src/lzo1x_c.c (== minilzo's lzo1x_1_compress), with the library's external
// dependencies (lzo_init, lzo_uint, lzo_bytep, LZO_E_* ...) replaced by the
// plain types this file already uses. The output format is untouched: matches
// are coded as M1/M2/M3/M4 and the stream ends with the 0x11 0x00 0x00 marker
// (M4_MARKER | 1), exactly as the standard encoder writes it, so any
// lzo1x_decompress - the game's included - decodes it.

#define LZO_D_BITS          14
#define LZO_D_SIZE          (1u << LZO_D_BITS)
#define LZO_D_MASK          (LZO_D_SIZE - 1)
#define LZO_D_HIGH          ((LZO_D_MASK >> 1) + 1)
#define LZO_M2_MAX_LEN      8
#define LZO_M2_MAX_OFFSET   0x0800
#define LZO_M3_MAX_OFFSET   0x4000
#define LZO_M4_MAX_OFFSET   0xbfff
#define LZO_M3_MARKER       32
#define LZO_M4_MARKER       16
#define LZO_DM(v)           ((unsigned)((v) & LZO_D_MASK))
#define LZO_DMUL(a,b)       ((unsigned)((a) * (b)))
#define LZO_DX2(p,s1,s2)    (((((unsigned)((p)[2]) << (s2)) ^ (p)[1]) << (s1)) ^ (p)[0])
#define LZO_DX3(p,s1,s2,s3) ((LZO_DX2((p) + 1, s2, s3) << (s1)) ^ (p)[0])
#define LZO_D_INDEX1(d,p)   d = LZO_DM(LZO_DMUL(0x21, LZO_DX3(p,5,5,6)) >> 5)
#define LZO_D_INDEX2(d,p)   d = (d & (LZO_D_MASK & 0x7ff)) ^ (LZO_D_HIGH | 0x1f)
#define LZO_PDIFF(a,b)      ((unsigned)((a) - (b)))

// Writes matches and stores trailing literals into the dictionary, then
// returns the number of bytes at the end of the input still left to emit.
unsigned Lzo1xDoCompress(const uint8_t* in, unsigned in_len, uint8_t* out,
                         unsigned* out_len, const uint8_t** dict)
{
    uint8_t* op = out;
    const uint8_t* ip = in;
    const uint8_t* ii = ip;
    const uint8_t* const in_end = in + in_len;
    const uint8_t* const ip_end = in + in_len - LZO_M2_MAX_LEN - 5;

    ip += 4;
    for (;;)
    {
        const uint8_t* m_pos;
        unsigned m_off = 0;
        unsigned m_len;
        unsigned dindex;

        LZO_D_INDEX1(dindex, ip);
        m_pos = dict[dindex];
        if (m_pos == nullptr || m_pos >= ip || (m_off = LZO_PDIFF(ip, m_pos)) > LZO_M4_MAX_OFFSET)
            goto literal;
        if (m_off <= LZO_M2_MAX_OFFSET || m_pos[3] == ip[3])
            goto try_match;
        LZO_D_INDEX2(dindex, ip);
        m_pos = dict[dindex];
        if (m_pos == nullptr || m_pos >= ip || (m_off = LZO_PDIFF(ip, m_pos)) > LZO_M4_MAX_OFFSET)
            goto literal;
        if (m_off <= LZO_M2_MAX_OFFSET || m_pos[3] == ip[3])
            goto try_match;
        goto literal;

    try_match:
        if (m_pos[0] != ip[0] || m_pos[1] != ip[1])
        {
        }
        else if (m_pos[2] == ip[2])
        {
            goto match;
        }

    literal:
        dict[dindex] = ip;
        ++ip;
        if (ip >= ip_end)
            break;
        continue;

    match:
        dict[dindex] = ip;
        if (LZO_PDIFF(ip, ii) > 0)
        {
            unsigned t = LZO_PDIFF(ip, ii);
            if (t <= 3)
                op[-2] |= static_cast<uint8_t>(t);
            else if (t <= 18)
                *op++ = static_cast<uint8_t>(t - 3);
            else
            {
                unsigned tt = t - 18;
                *op++ = 0;
                while (tt > 255)
                {
                    tt -= 255;
                    *op++ = 0;
                }
                *op++ = static_cast<uint8_t>(tt);
            }
            do *op++ = *ii++; while (--t > 0);
        }
        ip += 3;
        if (m_pos[3] != *ip++ || m_pos[4] != *ip++ || m_pos[5] != *ip++ ||
            m_pos[6] != *ip++ || m_pos[7] != *ip++ || m_pos[8] != *ip++)
        {
            --ip;
            m_len = LZO_PDIFF(ip, ii);
            if (m_off <= LZO_M2_MAX_OFFSET)
            {
                m_off -= 1;
                *op++ = static_cast<uint8_t>(((m_len - 1) << 5) | ((m_off & 7) << 2));
                *op++ = static_cast<uint8_t>(m_off >> 3);
            }
            else if (m_off <= LZO_M3_MAX_OFFSET)
            {
                m_off -= 1;
                *op++ = static_cast<uint8_t>(LZO_M3_MARKER | (m_len - 2));
                goto m3_m4_offset;
            }
            else
            {
                m_off -= 0x4000;
                *op++ = static_cast<uint8_t>(LZO_M4_MARKER | ((m_off & 0x4000) >> 11) | (m_len - 2));
                goto m3_m4_offset;
            }
        }
        else
        {
            // Declared without initialisers: the goto m3_m4_offset above jumps
            // into this scope, and MSVC rejects jumping over an initialisation.
            const uint8_t* end;
            const uint8_t* m;
            end = in_end;
            m = m_pos + LZO_M2_MAX_LEN + 1;
            while (ip < end && *m == *ip)
            {
                m++;
                ip++;
            }
            m_len = LZO_PDIFF(ip, ii);
            if (m_off <= LZO_M3_MAX_OFFSET)
            {
                m_off -= 1;
                if (m_len <= 33)
                    *op++ = static_cast<uint8_t>(LZO_M3_MARKER | (m_len - 2));
                else
                {
                    m_len -= 33;
                    *op++ = LZO_M3_MARKER | 0;
                    goto m3_m4_len;
                }
            }
            else
            {
                m_off -= 0x4000;
                if (m_len <= 9)
                    *op++ = static_cast<uint8_t>(LZO_M4_MARKER | ((m_off & 0x4000) >> 11) | (m_len - 2));
                else
                {
                    m_len -= 9;
                    *op++ = static_cast<uint8_t>(LZO_M4_MARKER | ((m_off & 0x4000) >> 11));
                m3_m4_len:
                    while (m_len > 255)
                    {
                        m_len -= 255;
                        *op++ = 0;
                    }
                    *op++ = static_cast<uint8_t>(m_len);
                }
            }
        m3_m4_offset:
            *op++ = static_cast<uint8_t>((m_off & 63) << 2);
            *op++ = static_cast<uint8_t>(m_off >> 6);
        }
        ii = ip;
        if (ip >= ip_end)
            break;
    }

    *out_len = LZO_PDIFF(op, out);
    return LZO_PDIFF(in_end, ii);
}

// Public entry point: returns the compressed size. `out` must be able to hold
// inLen + inLen / 16 + 64 + 3 bytes, and the result always ends in the LZO1X
// end marker 0x11 0x00 0x00. The dictionary lives on the stack - the generator
// is single threaded - and is zeroed so every empty bucket reads as "no match".
unsigned Lzo1xCompress(const uint8_t* in, size_t inLen, uint8_t* out)
{
    const uint8_t* dict[LZO_D_SIZE];
    std::memset(dict, 0, sizeof(dict));

    uint8_t* op = out;
    unsigned op_len = 0;
    unsigned t;

    if (inLen <= LZO_M2_MAX_LEN + 5)
    {
        t = static_cast<unsigned>(inLen);
    }
    else
    {
        t = Lzo1xDoCompress(in, static_cast<unsigned>(inLen), op, &op_len, dict);
        op += op_len;
    }

    if (t > 0)
    {
        const uint8_t* ii = in + inLen - t;
        if (op == out && t <= 238)
            *op++ = static_cast<uint8_t>(17 + t);
        else if (t <= 3)
            op[-2] |= static_cast<uint8_t>(t);
        else if (t <= 18)
            *op++ = static_cast<uint8_t>(t - 3);
        else
        {
            unsigned tt = t - 18;
            *op++ = 0;
            while (tt > 255)
            {
                tt -= 255;
                *op++ = 0;
            }
            *op++ = static_cast<uint8_t>(tt);
        }
        do *op++ = *ii++; while (--t > 0);
    }

    *op++ = LZO_M4_MARKER | 1;      // the LZO1X end-of-stream marker: 0x11
    *op++ = 0;
    *op++ = 0;
    return static_cast<unsigned>(op - out);
}

#undef LZO_D_BITS
#undef LZO_D_SIZE
#undef LZO_D_MASK
#undef LZO_D_HIGH
#undef LZO_M2_MAX_LEN
#undef LZO_M2_MAX_OFFSET
#undef LZO_M3_MAX_OFFSET
#undef LZO_M4_MAX_OFFSET
#undef LZO_M3_MARKER
#undef LZO_M4_MARKER
#undef LZO_DM
#undef LZO_DMUL
#undef LZO_DX2
#undef LZO_DX3
#undef LZO_D_INDEX1
#undef LZO_D_INDEX2
#undef LZO_PDIFF

void AppendPack5Section(std::vector<uint8_t>& out, const uint8_t* data, size_t size)
{
    std::vector<uint8_t> payload(size + size / 16 + 64 + 3);
    const unsigned compressed = Lzo1xCompress(data, size, payload.data());
    payload.resize(compressed);

    PutU16(out, compressed);                              // size_in
    PutU16(out, static_cast<unsigned>(size));             // size_out
    out.insert(out.end(), payload.begin(), payload.end());
}

// ---- format 80: one OverlayPack / OverlayDataPack section -----------------
// Faithful port of XCC's encode80 (shp_decode.cpp): an LZ77-style stream of
// literal runs, back-reference copies and fill runs. The previous port emitted
// only the literal-run form, which is legal but leaves the 512 x 512 overlay
// grid (almost entirely 0xFF = "no overlay") at its full 262144 bytes. The real
// encoder collapses such a run into a single fill command, which is where the
// bulk of the saved space comes from.

int RunLength(const uint8_t* r, const uint8_t* s_end)
{
    int count = 1;
    const uint8_t v = *r++;
    while (r < s_end && *r++ == v)
        ++count;
    return count;
}

// XCC's get_same(): the longest prefix shared by s[r..] and any earlier
// position s[q..], q < r. Ported from the inline asm to plain C++ (the asm also
// walks to the LAST candidate on ties, which the >= below reproduces).
void GetSame(const uint8_t* s, const uint8_t* r, const uint8_t* s_end,
             const uint8_t*& p, int& cb_p)
{
    int best = 0;
    p = s;
    for (const uint8_t* q = s; q < r; ++q)
    {
        const uint8_t* a = q;
        const uint8_t* b = r;
        int len = 0;
        while (b < s_end && *a == *b)
        {
            ++a;
            ++b;
            ++len;
        }
        if (len >= best)
        {
            best = len;
            p = q;
        }
    }
    cb_p = best;
}

void Write80C0(uint8_t*& w, int count, int p)
{
    *w++ = static_cast<uint8_t>(((count - 3) << 4) | (p >> 8));
    *w++ = static_cast<uint8_t>(p & 0xFF);
}

void Write80C1(uint8_t*& w, int count, const uint8_t* r)
{
    do
    {
        const int c_write = count < 0x40 ? count : 0x3F;
        *w++ = static_cast<uint8_t>(0x80 | c_write);
        if (c_write > 0)
            std::memcpy(w, r, static_cast<size_t>(c_write));
        r += c_write;
        w += c_write;
        count -= c_write;
    }
    while (count);
}

void Write80C2(uint8_t*& w, int count, int p)
{
    *w++ = static_cast<uint8_t>(0xC0 | (count - 3));
    *w++ = static_cast<uint8_t>(p & 0xFF);
    *w++ = static_cast<uint8_t>((p >> 8) & 0xFF);
}

void Write80C3(uint8_t*& w, int count, int v)
{
    *w++ = 0xFE;
    *w++ = static_cast<uint8_t>(count & 0xFF);
    *w++ = static_cast<uint8_t>((count >> 8) & 0xFF);
    *w++ = static_cast<uint8_t>(v);
}

void Write80C4(uint8_t*& w, int count, int p)
{
    *w++ = 0xFF;
    *w++ = static_cast<uint8_t>(count & 0xFF);
    *w++ = static_cast<uint8_t>((count >> 8) & 0xFF);
    *w++ = static_cast<uint8_t>(p & 0xFF);
    *w++ = static_cast<uint8_t>((p >> 8) & 0xFF);
}

void Flush80C1(uint8_t*& w, const uint8_t* r, const uint8_t*& copy_from)
{
    if (copy_from)
    {
        Write80C1(w, static_cast<int>(r - copy_from), copy_from);
        copy_from = nullptr;
    }
}

int Encode80(const uint8_t* s, uint8_t* d, int cb_s)
{
    const uint8_t* const s_end = s + cb_s;
    const uint8_t* r = s;
    uint8_t* w = d;
    const uint8_t* copy_from = nullptr;
    while (r < s_end)
    {
        const uint8_t* p;
        int cb_p;
        const int t = RunLength(r, s_end);
        GetSame(s, r, s_end, p, cb_p);
        if (t < cb_p && cb_p > 2)
        {
            Flush80C1(w, r, copy_from);
            if (cb_p - 3 < 8 && r - p < 0x1000)
                Write80C0(w, cb_p, static_cast<int>(r - p));
            else if (cb_p - 3 < 0x3E)
                Write80C2(w, cb_p, static_cast<int>(p - s));
            else
                Write80C4(w, cb_p, static_cast<int>(p - s));
            r += cb_p;
        }
        else
        {
            if (t < 3)
            {
                if (!copy_from)
                    copy_from = r;
            }
            else
            {
                Flush80C1(w, r, copy_from);
                Write80C3(w, t, *r);
            }
            r += t;
        }
    }
    Flush80C1(w, r, copy_from);
    Write80C1(w, 0, nullptr);
    return static_cast<int>(w - d);
}

void AppendPack80Section(std::vector<uint8_t>& out, const uint8_t* data, size_t size)
{
    std::vector<uint8_t> payload(size + size / 30 + 16);
    const int packed = Encode80(data, payload.data(), static_cast<int>(size));
    payload.resize(static_cast<size_t>(packed));

    PutU24(out, static_cast<unsigned>(payload.size()));
    out.push_back(0x20);
    out.insert(out.end(), payload.begin(), payload.end());
}

// ---- base64 (XCC's encode64_table) ----------------------------------------

const char kBase64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string EncodeBase64(const std::vector<uint8_t>& data)
{
    std::string out;
    out.reserve(((data.size() + 2) / 3) * 4);

    size_t i = 0;
    while (i + 3 <= data.size())
    {
        const unsigned v = (static_cast<unsigned>(data[i]) << 16)
                         | (static_cast<unsigned>(data[i + 1]) << 8)
                         | static_cast<unsigned>(data[i + 2]);
        out += kBase64[(v >> 18) & 0x3F];
        out += kBase64[(v >> 12) & 0x3F];
        out += kBase64[(v >> 6) & 0x3F];
        out += kBase64[v & 0x3F];
        i += 3;
    }
    if (data.size() - i == 1)
    {
        const unsigned v = static_cast<unsigned>(data[i]) << 16;
        out += kBase64[(v >> 18) & 0x3F];
        out += kBase64[(v >> 12) & 0x3F];
        out += '=';
        out += '=';
    }
    else if (data.size() - i == 2)
    {
        const unsigned v = (static_cast<unsigned>(data[i]) << 16)
                         | (static_cast<unsigned>(data[i + 1]) << 8);
        out += kBase64[(v >> 18) & 0x3F];
        out += kBase64[(v >> 12) & 0x3F];
        out += kBase64[(v >> 6) & 0x3F];
        out += '=';
    }
    return out;
}

// A packed blob becomes numbered 70-character INI lines (sub_526E80).
void AppendPackedSection(std::string& text, const char* name,
                         const std::vector<uint8_t>& packed)
{
    const std::string b64 = EncodeBase64(packed);

    text += '[';
    text += name;
    text += "]\n";

    int line = 1;
    for (size_t pos = 0; pos < b64.size(); pos += 70)
    {
        char key[16];
        std::snprintf(key, sizeof(key), "%d", line++);
        text += key;
        text += '=';
        text += b64.substr(pos, 70);
        text += '\n';
    }
    text += '\n';
}

std::string Int(int v)
{
    char buf[24];
    std::snprintf(buf, sizeof(buf), "%d", v);
    return buf;
}

std::string Real(double v)
{
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%f", v);
    return buf;
}

// One entry of the RMG's per-time-of-day light lists, as a 0..1 factor.
double LightFactor(const std::vector<int>& list, int index, double fallback)
{
    if (index < 0 || index >= static_cast<int>(list.size()))
        return fallback;
    return static_cast<double>(list[index]) / 100.0;
}

// FA2's MapCode.cpp calcXPos / calcYPos. The multiplayer [Header] block stores
// the starting points and the map rect in the engine's flat "iso pixel" space,
// not in cells:
//     x1 = x*256+128 ; y1 = y*256+128
//     x2 = (x1-y1)*30 ; y2 = (x1+y1)*15
//     calcXPos = (x2/256 + 512*30) / 60
//     calcYPos = (y2/256) / 30
// Every division is an integer division, so the results truncate toward zero.
// The caller passes the cell's (Y, X): FA2's header loop and its waypoint loop
// both work in the swapped "WS" order (see MC_GetHeaderRect in MapCode.cpp).
static int HeaderX(int x, int y)
{
    const int x1 = x * 256 + 128;
    const int y1 = y * 256 + 128;
    const int x2 = (x1 - y1) * 30;
    return (x2 / 256 + 512 * 30) / 60;
}

static int HeaderY(int x, int y)
{
    const int x1 = x * 256 + 128;
    const int y1 = y * 256 + 128;
    const int y2 = (x1 + y1) * 15;
    return (y2 / 256) / 30;
}

}   // namespace

// ---------------------------------------------------------------------------
// RandomMapGenerator::SaveMapFile
//
// Writes the finished map. The caller supplies the full path; the UI puts it
// next to the executable. Everything is read from the generator's own state:
// the cells (cellSlots_), the three object ledgers and the rolled settings.
// ---------------------------------------------------------------------------
bool RandomMapGenerator::SaveMapFile(const wchar_t* path)
{
    if (!path)
        return false;

    MapCell* const* slots = GetCellSlots();
    if (!slots)
        return false;

    // The port's slot array is slotRows_ * 512, slotRows_ = mapWidth + mapHeight
    // + 1 (AllocateCells). Walk it whole and skip the empty slots, so no cell
    // can be missed regardless of how the diamond was laid out.
    const int rows = size_.mapWidth + size_.mapHeight + 1;

    // ---- 1. [IsoMapPack5]: 11 bytes per cell ------------------------------
    // The same records are collected in readable form as well, because the
    // in-game check of whether the region connections line up needs the
    // per-cell heights spelled out; the dump goes next to the .map as
    // "<name>.isopack5.txt". Column meanings:
    //
    //   X Y        the cell's map coordinates
    //   tile       IsoTileTypeIndex
    //   bMapData   the record's bytes 6..7 (the tile dword's high half, 0)
    //   bSubTile   the record's byte 8  = CellClass::Height  (+0x11A)
    //   bHeight    the record's byte 9  = CellClass::Level   (+0x11B)
    //   bMapData2  the record's byte 10 = IsIceGrowthAllowed (+0x119), 0 here
    //   then the port's own Height / Level / SlopeIndex / LandType / Passability,
    //   then the 11 raw bytes in hex.
    //   (The offsets are YRpp's CellClass order: TubeIndex +0x116, unknown_118,
    //    IsIceGrowthAllowed +0x119, Height +0x11A, Level +0x11B, SlopeIndex
    //    +0x11C - i.e. file[8] really is Height and file[9] really is Level.)
    std::vector<uint8_t> iso;
    std::string dump;
    iso.reserve(static_cast<size_t>(size_.width) * size_.height * 11);
    dump.reserve(static_cast<size_t>(size_.width) * size_.height * 64);

    dump += "; IsoMapPack5 uncompressed data - one line per cell, in pack order.\n";
    dump += "; X Y tile bMapData bSubTile bHeight bMapData2 = Height Level LandType SlopeIndex Passability | hex\n";

    int cellCount = 0;
    int foundationTilesStamped = 0;   // [port-only] 地基占位瓦替换计数
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < 512; ++x)
        {
            const MapCell* cell = slots[512 * y + x];
            if (!cell)
                continue;

            const int cellX = static_cast<int16_t>(cell->MapCoords & 0xFFFF);
            const int cellY = static_cast<int16_t>((cell->MapCoords >> 16) & 0xFFFF);

            // Write the raw tile index. A cell the RMG never tiled keeps
            // tile 0 - this is NOT "no tile": the released engine treats 0 as
            // a legal clear placeholder and fills it on load (Recalc / the
            // map-load terrain pass). Vanilla RMG maps carry thousands of
            // tile-0 cells (measured: 1999 on one L8 plateau layer alone),
            // including unfilled cliff SW-diagonal cells that the loader
            // stitches into the facade. Writing 0xFFFF here instead marks an
            // explicit EMPTY cell the loader never fills - that left one-cell
            // gaps between neighbouring cliff pieces.
            int tile = cell->IsoTileTypeIndex;

            // [port-only] A tech-building foundation cell MUST carry a real,
            // flat clear tile in the saved file. The game engine fills tile 0
            // on load, but FA2's minimap paints a cell only when its tile has
            // an on-disk TMP frame for its Height sub-frame (Mini_UpdatePos
            // returns early on tile 0), so the building's house-colour dot was
            // never drawn - manually placed buildings work in FA2 precisely
            // because the editor stamps a real ground tile under them
            // (measured: sov01umd GAPOWR sits on tile 493). Do the same here.
            if ((cell->AltFlags & AltCellFlags_ContainsBuilding) != 0
                && (tile == 0 || tile == 0xFFFF)
                && clearTileIndex_ >= 0)
            {
                tile = clearTileIndex_;
                ++foundationTilesStamped;
            }

            uint8_t record[11];
            record[0] = static_cast<uint8_t>(cellX & 0xFF);                  // +0 X
            record[1] = static_cast<uint8_t>((cellX >> 8) & 0xFF);
            record[2] = static_cast<uint8_t>(cellY & 0xFF);                  // +2 Y
            record[3] = static_cast<uint8_t>((cellY >> 8) & 0xFF);
            record[4] = static_cast<uint8_t>(tile & 0xFF);                   // +4 tile
            record[5] = static_cast<uint8_t>((tile >> 8) & 0xFF);
            record[6] = 0;                                                   // +6 bMapData
            record[7] = 0;
            record[8] = static_cast<uint8_t>(cell->Height);                  // +8 Height
            record[9] = static_cast<uint8_t>(cell->Level);                   // +9 Level
            record[10] = 0;                                                  // +10 IsIceGrowthAllowed

            iso.insert(iso.end(), record, record + 11);
            ++cellCount;

            char hex[24];
            for (int i = 0; i < 11; ++i)
                std::snprintf(hex + i * 2, 3, "%02X", record[i]);

            char line[192];
            std::snprintf(line, sizeof(line),
                          "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
                          cellX, cellY, tile,
                          record[6] | (record[7] << 8),
                          record[8], record[9], record[10],
                          cell->Height, cell->Level,
                          cell->LandType, cell->SlopeIndex, cell->Passability,
                          hex);
            dump += line;
        }
    }
    dump += "; cells = " + Int(cellCount) + "\n";
    DiagLog("SAVE-FILE clearTileIndex=%d foundation placeholder cells stamped=%d",
            clearTileIndex_, foundationTilesStamped);

    std::vector<uint8_t> isoPack;
    for (size_t off = 0; off < iso.size(); off += 8192)
        AppendPack5Section(isoPack, &iso[off], std::min<size_t>(8192, iso.size() - off));

    // ---- 2. [OverlayPack] / [OverlayDataPack]: 512 x 512, X + 512 * Y -----
    const size_t kGridSize = 512u * 512u;
    std::vector<uint8_t> overlay(kGridSize, 0xFF);      // 0xFF = no overlay
    std::vector<uint8_t> overlayData(kGridSize, 0x00);

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < 512; ++x)
        {
            const MapCell* cell = slots[512 * y + x];
            if (!cell)
                continue;
            if (cell->OverlayTypeIndex < 0 || cell->OverlayTypeIndex > 0xFE)
                continue;

            const size_t index = static_cast<size_t>(x) + 512u * static_cast<size_t>(y);
            if (index >= kGridSize)
                continue;

            overlay[index] = static_cast<uint8_t>(cell->OverlayTypeIndex);
            overlayData[index] = static_cast<uint8_t>(cell->OverlayData);
        }
    }

    std::vector<uint8_t> overlayPack;
    std::vector<uint8_t> overlayDataPack;
    for (size_t section = 0; section < 32; ++section)   // 262144 / 8192
    {
        AppendPack80Section(overlayPack, &overlay[section * 8192], 8192);
        AppendPack80Section(overlayDataPack, &overlayData[section * 8192], 8192);
    }

    // ---- 2b. the multiplayer [Header] rectangle ---------------------------
    // FA2's MC_GetHeaderRect (MapCode.cpp:75-149) walks the whole iso square and
    // keeps every cell that falls inside the visible ("local") rect, then takes
    // the min/max of the flat iso-pixel coordinates calcXPos / calcYPos over
    // those cells. The four tests are FA2's own four conditions with the port's
    // numbers filled in (LocalRect = 2,5,width,height ; PlayRect = mapWidth x
    // mapHeight):
    //     x + y >  playWidth + 2*localTop + height
    //     x + y <= playWidth + 2*(localTop + localHeight + 1) + height
    //     x - y <  2*(localLeft + localWidth) - playWidth
    //     y - x <  playWidth - 2*localLeft
    // FA2's loop x is the cell's Y and its loop y the cell's X ("WS coordinate
    // system"), so the sum is cellX + cellY and the height is the cell's own
    // Height field. Cells outside the diamond have no slot entry and read as
    // height 0, exactly like FA2's GetHeightAt on an empty cell. A single-player
    // map carries no rectangle, so this runs for the multiplayer layout only.
    int headerStartX = 0;
    int headerStartY = 0;
    int headerWidth = 0;
    int headerHeight = 0;
    if (config_.multiplayer)
    {
        const int localLeft = 2;                        // [Map] LocalSize left
        const int localTop = 5;                         // [Map] LocalSize top
        const int localWidth = size_.width;             // [Map] LocalSize width
        const int localHeight = size_.height;           // [Map] LocalSize height
        const int playWidth = size_.mapWidth;           // [Map] Size width
        const int isoSize = size_.mapWidth + size_.mapHeight;

        int leastX = 10000;
        int leastY = 10000;
        int mostX = 0;
        int mostY = 0;

        for (int loopX = 0; loopX < isoSize; ++loopX)       // FA2 x = cell Y
        {
            for (int loopY = 0; loopY < isoSize; ++loopY)   // FA2 y = cell X
            {
                const int cellX = loopY;
                const int cellY = loopX;
                const MapCell* cell = (cellX < 512 && cellY < rows)
                                          ? slots[512 * cellY + cellX] : nullptr;
                const int height = cell ? cell->Height : 0;

                if (!(loopX + loopY > playWidth + 2 * localTop + height))
                    continue;
                if (!(loopX + loopY <= playWidth + 2 * (localTop + localHeight + 1) + height))
                    continue;
                if (!(loopX - loopY < 2 * (localLeft + localWidth) - playWidth))
                    continue;
                if (!(loopY - loopX < playWidth - 2 * localLeft))
                    continue;

                const int rx = HeaderX(loopX, loopY);
                const int ry = HeaderY(loopX, loopY);
                if (rx < leastX) leastX = rx;
                if (rx > mostX) mostX = rx;
                if (ry < leastY) leastY = ry;
                if (ry > mostY) mostY = ry;
            }
        }

        headerStartX = leastX;
        headerStartY = leastY;
        headerWidth = mostX - leastX;
        headerHeight = mostY - leastY;
    }

    // ---- 3. the text -------------------------------------------------------
    const int timeOfDay = config_.timeOfDay;
    const bool snow = (config_.theater != 0);

    std::string text;
    text += "; Generated by the MapGenerator random map generator (RMG port)\n";
    text += "; IsoMapPack5 / OverlayPack / OverlayDataPack follow the engine's\n";
    text += "; own save path (MapClass writer sub_4AD7E0).\n\n";

    text += "[Header]\n";
    if (config_.multiplayer)
    {
        // FA2 writes this block for multiplayer maps only (FinalSunDlg.cpp
        // SaveMap, RA2_MODE + IsMultiplayer). Width/Height/StartX/StartY are the
        // iso-pixel rect of the visible area and Waypoint1..8 the starting points
        // in the same iso-pixel space; the game's multiplayer lobby uses them to
        // draw the map preview and place the players. Starts beyond the eighth
        // read 0,0, as FA2 leaves them.
        text += "Width=" + Int(headerWidth) + "\n";
        text += "Height=" + Int(headerHeight) + "\n";
        text += "StartX=" + Int(headerStartX) + "\n";
        text += "StartY=" + Int(headerStartY) + "\n";
        for (int i = 0; i < 8; ++i)
        {
            text += "Waypoint" + Int(i + 1) + "=";
            if (i < static_cast<int>(startingPoints_.size()))
            {
                const CellStruct& c = startingPoints_[i].coords;
                text += Int(HeaderX(c.Y, c.X));
                text += ',';
                text += Int(HeaderY(c.Y, c.X));
            }
            else
            {
                text += "0,0";
            }
            text += "\n";
        }
    }
    text += "NumberStartingPoints=" + Int(static_cast<int>(startingPoints_.size())) + "\n\n";

    text += "[Basic]\n";
    text += "Name=No name\n";
    // A multiplayer map carries no [Basic] Player key (the shipped .yrm files
    // have none); the single-player layout names the player's house there.
    if (!config_.multiplayer)
        text += "Player=Neutral House\n";
    text += "Percent=0\n";
    text += "GameMode=standard\n";
    // HomeCell / AltHomeCell are the single-player spawn cells. Multiplayer maps
    // take their starts from [Header] Waypoint1..8 instead and keep the shipped
    // maps' placeholders (98 / 99).
    if (config_.multiplayer)
    {
        text += "HomeCell=98\n";
        text += "AltHomeCell=99\n";
    }
    else
    {
        text += "HomeCell=" + Int(startingPoints_.empty() ? 98 : startingPoints_[0].index) + "\n";
        text += "AltHomeCell=" + Int(startingPoints_.size() > 1 ? startingPoints_[1].index : 99) + "\n";
    }
    text += "InitTime=10000\n";
    text += "Official=no\n";
    text += "EndOfGame=no\n";
    text += "FreeRadar=no\n";
    text += "MaxPlayer=" + Int(config_.playerCount) + "\n";
    text += "MinPlayer=2\n";
    text += "SkipScore=no\n";
    text += "TrainCrate=no\n";
    text += "TruckCrate=no\n";
    text += "OneTimeOnly=no\n";
    text += "CarryOverCap=0\n";
    text += "NewINIFormat=4\n";
    text += "NextScenario=\n";
    text += "AltNextScenario=\n";
    text += "SkipMapSelect=no\n";
    text += "CarryOverMoney=0.000000\n";
    // The key that tells FA2 (and the game) which layout this file is:
    // IsMultiplayer() (MapData.cpp:6088) reports TRUE on MultiplayerOnly!=0 and
    // the .yrm files carry 1 while a normal .map carries 0.
    text += "MultiplayerOnly=";
    text += Int(config_.multiplayer ? 1 : 0);
    text += "\n";
    text += "IceGrowthEnabled=yes\n";
    text += "VeinGrowthEnabled=yes\n";
    text += "TiberiumGrowthEnabled=yes\n";
    text += "IgnoreGlobalAITriggers=no\n";
    text += "TiberiumDeathToVisceroid=no\n\n";

    text += "[Map]\n";
    text += "Size=0,0," + Int(size_.mapWidth) + "," + Int(size_.mapHeight) + "\n";
    text += "Theater=";
    text += snow ? "SNOW" : "TEMPERATE";
    text += "\n";
    // [Map] LocalSize is the visible rect, i.e. the port's VisibleRect.
    text += "LocalSize=2,5," + Int(size_.width) + "," + Int(size_.height) + "\n\n";

    text += "[Lighting]\n";
    text += "Ambient=" + Real(LightFactor(snow ? settings_.SnowAmbientLight
                                            : settings_.TemperateAmbientLight,
                                        timeOfDay, 1.0)) + "\n";
    text += "Red=" + Real(LightFactor(snow ? settings_.SnowAmbientRed
                                          : settings_.TemperateAmbientRed,
                                      timeOfDay, 1.0)) + "\n";
    text += "Green=" + Real(LightFactor(snow ? settings_.SnowAmbientGreen
                                            : settings_.TemperateAmbientGreen,
                                        timeOfDay, 1.0)) + "\n";
    text += "Blue=" + Real(LightFactor(snow ? settings_.SnowAmbientBlue
                                           : settings_.TemperateAmbientBlue,
                                       timeOfDay, 1.0)) + "\n";
    text += "Level=" + Real(LightFactor(settings_.LevelLightSettings, timeOfDay, 0.0)) + "\n\n";

    // ---- 4. the three packed sections -------------------------------------
    AppendPackedSection(text, "IsoMapPack5", isoPack);
    AppendPackedSection(text, "OverlayDataPack", overlayDataPack);
    AppendPackedSection(text, "OverlayPack", overlayPack);

    // ---- 5. the object ledgers --------------------------------------------
    // The houses. Every object in the ledgers below names an owner section, and
    // that owner has to be registered here or the editor treats the object as
    // unowned and does not show it. The generator only ever places neutral
    // buildings (the tech buildings of sub_5A95B0 and the bridge repair hut).
    //
    // The two layouts differ, and FA2's CHouses::OnPreparehouses
    // (Houses.cpp:249-302) is the reference:
    //   single player (.map) - [Countries] names the rules country, [Houses]
    //     names the map's own house section ("Neutral House") at the same rules
    //     index 12, and the [Neutral House] section carries the attributes
    //     (Color drives the editor's tint). The shipped all01umd.map does this.
    //   multiplayer (.yrm) - the whole rules [Countries] list is registered as
    //     the map's house list: [Houses] <i>=<country> for every country plus one
    //     [<country>] attribute section each. There is no [Countries] section on
    //     a multiplayer map - the shipped .yrm files carry none. The neutral
    //     entry of that list keeps the generated buildings owned.
    const char* neutralOwner = config_.multiplayer ? "Neutral" : "Neutral House";

    if (config_.multiplayer)
    {
        if (!multiplayerHouses_.empty())
        {
            text += "[Houses]\n";
            for (size_t i = 0; i < multiplayerHouses_.size(); ++i)
            {
                text += Int(static_cast<int>(i));
                text += '=';
                text += multiplayerHouses_[i].country;
                text += '\n';
            }
            text += '\n';

            for (size_t i = 0; i < multiplayerHouses_.size(); ++i)
            {
                const MultiplayerHouse& h = multiplayerHouses_[i];
                text += "[";
                text += h.country;
                text += "]\n";
                text += "IQ=0\n";
                text += "Edge=North\n";
                text += "Color=";
                text += h.color;
                text += "\n";
                text += "Allies=";
                text += h.country;
                text += "\n";
                text += "Country=";
                text += h.country;
                text += "\n";
                text += "Credits=0\n";
                text += "NodeCount=0\n";
                text += "TechLevel=1\n";
                text += "PercentBuilt=0\n";
                text += "PlayerControl=no\n\n";
            }
        }
        else
        {
            // Rules INI missing or empty: fall back to the neutral house alone so
            // the generated buildings still have an owner to name.
            text += "[Houses]\n";
            text += "12=Neutral\n\n";

            text += "[Neutral]\n";
            text += "IQ=0\n";
            text += "Edge=North\n";
            text += "Color=Grey\n";
            text += "Allies=Neutral\n";
            text += "Country=Neutral\n";
            text += "Credits=0\n";
            text += "NodeCount=0\n";
            text += "TechLevel=1\n";
            text += "PercentBuilt=0\n";
            text += "PlayerControl=no\n\n";
        }
    }
    else if (!structures_.empty())
    {
        text += "[Countries]\n";
        text += "12=Neutral\n\n";

        text += "[Houses]\n";
        text += "12=Neutral House\n\n";

        text += "[Neutral House]\n";
        text += "IQ=5\n";
        text += "Edge=North\n";
        text += "Color=Grey\n";
        text += "Allies=Neutral House\n";
        text += "Country=Neutral\n";
        text += "Credits=0\n";
        text += "NodeCount=0\n";
        text += "TechLevel=10\n";
        text += "PercentBuilt=100\n";
        text += "PlayerControl=no\n\n";
    }

    // [Waypoints] keys on the waypoint number, values are the packed cell
    // X + 1000*Y (FA2 / the engine decode X = value mod 1000, Y = value / 1000).
    text += "[Waypoints]\n";
    for (size_t i = 0; i < startingPoints_.size(); ++i)
    {
        const StartingPointRecord& sp = startingPoints_[i];
        text += Int(sp.index);
        text += '=';
        text += Int(sp.coords.X + 1000 * sp.coords.Y);
        text += '\n';
    }
    text += '\n';

    // [Terrain] keys on the packed cell, values are the type name
    // (CMapData::UpdateTerrain: PosToXY(key), value = the type).
    if (!terrainObjects_.empty())
    {
        text += "[Terrain]\n";
        for (size_t i = 0; i < terrainObjects_.size(); ++i)
        {
            const MapTerrainObject& t = terrainObjects_[i];
            if (!t.typeName)
                continue;
            // packed cell 与 [Waypoints] 一致：cellNum = X + 1000*Y，引擎
            // PosToXY 按 x=num%1000、y=num/1000 还原。先前误写成 X*1000+Y，
            // X/Y 转置使 FA2 把树读到镜像格（原本在陆地的树落进水里）。
            text += Int(t.coords.X + 1000 * t.coords.Y);
            text += '=';
            text += t.typeName;
            text += '\n';
        }
        text += '\n';
    }

    // [Structures]: the 17-field line the shipped maps use.
    if (!structures_.empty())
    {
        text += "[Structures]\n";
        int line = 0;
        for (size_t i = 0; i < structures_.size(); ++i)
        {
            const MapStructure& s = structures_[i];
            if (!s.typeName)
                continue;
            text += Int(line++);
            text += '=';
            // The owner is the house section name registered above: the port only
            // places neutral buildings, so multiplayer names the rules' "Neutral"
            // country and single player its own "Neutral House" section. The
            // strength is 256 (full health, what FA2 fills in for a newly placed
            // building).
            text += config_.multiplayer ? neutralOwner
                                        : (s.houseName ? s.houseName : "Neutral House");
            text += ',';
            text += s.typeName;
            text += ",256,";
            // Field order from CMapData::AddStructure (MapData.cpp:2493):
            // house,type,strength,Y,X,direction,...; FA2 writes
            // x = pos % IsoSize into field 4 and y = pos / IsoSize into
            // field 3 (MapData.cpp:2459-2460), and the IsoMapPack5 record
            // header is (wX=row at +0, wY=column at +2). The port's
            // coords.X is that ROW and coords.Y that COLUMN (SaveMapFile
            // writes record[0]=X, record[2]=Y), so field 3 must be coords.X
            // and field 4 coords.Y. Writing them swapped made the editor /
            // game place the building on the transposed cell - which on the
            // measured maps was a ramp or cliff facade (verified against
            // rmg_20261003_143645 and the shipped sov01umd.map).
            text += Int(s.coords.X);
            text += ',';
            text += Int(s.coords.Y);
            text += ',';
            text += Int(s.facing);
            text += ",None,0,0,1,0,0,None,None,None,1,0\n";
        }
        text += '\n';
    }

    // ---- 6. write the map out ---------------------------------------------
    FILE* file = nullptr;
    if (_wfopen_s(&file, path, L"wb") != 0 || !file)
        return false;

    const size_t written = std::fwrite(text.data(), 1, text.size(), file);
    std::fclose(file);

    // ---- 7. and the readable dump of the very same records ----------------
    // "<the map>.isopack5.txt". The pack in the .map is base64 of an LZO stream,
    // so per-cell heights cannot be eyeballed there; this file spells them out.
    // 这是给开发期逐格核对用的转储，只在 Debug 下生成；Release（定义了
    // NDEBUG）不写这个文件，使用者的输出文件夹里只留成品地图。
#ifndef NDEBUG
    {
        std::wstring dumpPath(path);
        const size_t dot = dumpPath.find_last_of(L'.');
        if (dot != std::wstring::npos)
            dumpPath.erase(dot);
        dumpPath += L".isopack5.txt";

        FILE* dumpFile = nullptr;
        if (_wfopen_s(&dumpFile, dumpPath.c_str(), L"wb") == 0 && dumpFile)
        {
            std::fwrite(dump.data(), 1, dump.size(), dumpFile);
            std::fclose(dumpFile);
        }
    }
#endif

    return written == text.size();
}

// ---------------------------------------------------------------------------
// RandomMapGenerator::SaveStageSnapshot
//
// [port-only diagnostic] The "old school" work flow: after each pipeline step
// the caller wants a FA2-readable snapshot of the map exactly as it looks at
// that moment, so a step-by-step diff can be eyeballed in the editor.
//
// The snapshot is an ordinary ".map" written by SaveMapFile, so the IsoMapPack5
// and overlay packs are the real compressed streams FA2 loads - not a text form.
// It goes to the folder the finished map goes to (the UI-selected output
// folder, by default the exe's own folder) and is named
// "<YYYYMMDD_HHMMSS>_<stageName>.map", so a batch of stages sorts by time while
// the stage still reads off the file name.
// ---------------------------------------------------------------------------
void RandomMapGenerator::SaveStageSnapshot(const char* stageName)
{
    if (stageName == nullptr || *stageName == '\0')
        return;

    // Same output directory the finished map uses (outputDir_, trailing slash).
    CreateDirectoryW(outputDir_.c_str(), nullptr);   // already there -> ignored

    wchar_t stage[128] = {};
    MultiByteToWideChar(CP_ACP, 0, stageName, -1, stage, ARRAYSIZE(stage));

    SYSTEMTIME now = {};
    GetLocalTime(&now);

    wchar_t stamp[64] = {};
    swprintf_s(stamp, ARRAYSIZE(stamp),
               L"%04d%02d%02d_%02d%02d%02d_%s.map",
               now.wYear, now.wMonth, now.wDay,
               now.wHour, now.wMinute, now.wSecond, stage);

    const std::wstring path = outputDir_ + stamp;
    SaveMapFile(path.c_str());
}

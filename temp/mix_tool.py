#!/usr/bin/env python3
"""mix_tool.py - read / extract Westwood MIX archives (incl. encrypted index).

Algorithm source: D:\\新建文件夹\\VSProject\\CCmix
  src/mix_header.cpp      header layout, RSA keysource, Blowfish index decryption
  src/mix_dexoder.cpp     XCC-style keysource -> Blowfish key (public exponent)
  src/mixid.cpp           file id from name (RA rotate-add, RA2 CRC32)
  src/mix_db_gamedb.cpp   "global mix database.dat", 4 tables TD/RA/TS/RA2
  src/mix_db_lmd.cpp      per-archive name list ("local mix database.dat")

Commands
  selftest                                  Blowfish + pi-constant self check
  keytest   <mix>                           show which key derivation validates
  list      <mix> [--gmd P] [--game G]
  dump      <mix> <name|[id]HEX> <outfile>  [--gmd P] [--game G]
  extract   <mix> <outdir> [substr ...]     [--flat] [--gmd P] [--game G]

G is one of td ra ts ra2; default is guessed from the archive name ("*md*" -> ra2).
Nested .mix/.mmx entries are opened again and extracted into a sub directory
unless --flat is given.
"""

import os
import struct
import sys
import zlib

# ---------------------------------------------------------------------------
# Blowfish - the P array and the four S boxes are the hex digits of pi.
# ---------------------------------------------------------------------------
_PI_HEX = None
_P = None
_S = None


def _pi_hex_digits(count):
    """`count` hex digits of pi after the point, e.g. "243F6A88...".

    Machin's formula in fixed point: pi = 16*atan(1/5) - 4*atan(1/239).
    """
    guard = 16
    unity = 16 ** (count + guard)

    def atan_inv(x):
        total = term = unity // x
        x2 = x * x
        k = 1
        while True:
            term //= x2
            if not term:
                break
            t = term // (2 * k + 1)
            if t:
                total += t if (k % 2 == 0) else -t
            k += 1
        return total

    pi = 16 * atan_inv(5) - 4 * atan_inv(239)
    return '%x' % (pi >> guard)


def _constants():
    global _PI_HEX, _P, _S
    if _P is not None:
        return
    _PI_HEX = _pi_hex_digits(18 * 8 + 4 * 256 * 8)[1:]      # drop the leading "3"
    words = [int(_PI_HEX[i * 8:i * 8 + 8], 16) for i in range(1042)]
    _P = words[:18]
    _S = [words[18 + b * 256: 18 + (b + 1) * 256] for b in range(4)]


class Blowfish(object):
    """ECB Blowfish, 8 byte blocks, big endian (the CryptoPP default)."""

    def __init__(self, key):
        _constants()
        self.p = list(_P)
        s = [list(box) for box in _S]
        self.s = s
        n = len(key)
        j = 0
        for i in range(18):
            data = 0
            for _ in range(4):
                data = ((data << 8) | key[j % n]) & 0xFFFFFFFF
                j += 1
            self.p[i] ^= data
        l = r = 0
        for i in range(0, 18, 2):
            l, r = self._encrypt(l, r)
            self.p[i] = l
            self.p[i + 1] = r
        for box in s:
            for i in range(0, 256, 2):
                l, r = self._encrypt(l, r)
                box[i] = l
                box[i + 1] = r

    def _f(self, x):
        s = self.s
        return ((((s[0][(x >> 24) & 0xFF] + s[1][(x >> 16) & 0xFF]) & 0xFFFFFFFF)
                 ^ s[2][(x >> 8) & 0xFF]) + s[3][x & 0xFF]) & 0xFFFFFFFF

    def _encrypt(self, l, r):
        p = self.p
        f = self._f
        for i in range(16):
            l ^= p[i]
            r ^= f(l)
            l, r = r, l
        l, r = r, l
        r ^= p[16]
        l ^= p[17]
        return l, r

    def _decrypt(self, l, r):
        p = self.p
        f = self._f
        for i in range(17, 1, -1):
            l ^= p[i]
            r ^= f(l)
            l, r = r, l
        l, r = r, l
        r ^= p[1]
        l ^= p[0]
        return l, r

    def enc_block(self, block):
        l, r = struct.unpack('>II', block)
        l, r = self._encrypt(l, r)
        return struct.pack('>II', l, r)

    def dec_block(self, block):
        l, r = struct.unpack('>II', block)
        l, r = self._decrypt(l, r)
        return struct.pack('>II', l, r)


# ---------------------------------------------------------------------------
# RSA keysource -> Blowfish key.
#
# The 80 bytes following the 4 flag bytes are two little endian 40 byte blocks
# encrypted with Westwood's *private* key; the public exponent recovers them:
#   mod = BE of the 40 bytes inside the ASN.1 blob below, exp = 0x10001
# (mix_dexoder.cpp get_blowfish_key).  Each recovered block contributes its low
# 39 bytes, little endian; the first 56 bytes of the two are the Blowfish key
# (mix_dexoder.cpp process_predata, a = (bitlen(mod)-1-1)/8 = 39).
#
# mix_header.cpp setKey() computes the same layout with the private exponent,
# so both are tried and the one that yields a sane index wins.
# ---------------------------------------------------------------------------
PUBKEY_B64 = "AihRvNoIbTn85FZRYNZRcT+i6KpU+maCsEqr3Q5q+LDB5tH7Tz2qQ38V"
PRVKEY_B64 = "AigKVje8mROcR8QixnxUEF5b29Curkq01DNDWCdOG99XBqH79OaCiTCB"
PUBKEY_HEX = "51bcda086d39fce4565160d651713fa2e8aa54fa6682b04aabdd0e6af8b0c1e6d1fb4f3daa437f15"
PRVKEY_HEX = "0a5637bc99139c47c422c67c54105e5bdbd0aeae4ab4d4334358274e1bdf5706a1fbf4e682893081"

import base64


def _asn1_int(b64):
    blob = base64.b64decode(b64)
    assert blob[0] == 2, "not an ASN.1 INTEGER"
    return int.from_bytes(blob[2:42], 'big')          # 40 byte modulus / exponent


RSA_MOD = _asn1_int(PUBKEY_B64)
RSA_PRV_B64 = _asn1_int(PRVKEY_B64)
RSA_PRV_HEX = int(PRVKEY_HEX, 16)
RSA_PUB_EXP = 0x10001

KEY_CACHE = {}


def _key_candidates(keysource):
    """Yield (label, 56 byte key), most likely construction first.

    What the reader (mix_header.cpp setKey()) does:

        keybuf = keysource reversed (all 80 bytes)
        k1 = Integer(keybuf +  0, 40)      # big endian
        k2 = Integer(keybuf + 40, 40)      # big endian
        k1 = k1 ** E mod n ; k2 = k2 ** E mod n
        x  = (k1 << 312) + k2
        x.Encode(buf, 56)                  # big endian
        key = buf reversed                 # little endian

    E is the *public* exponent 0x10001, not the private one: CryptoPP's
    RSA::PrivateKey::ApplyFunction ends up calling RSAFunction::ApplyFunction,
    which uses m_e.  The writer (setKeySource) initialises m_e = PRVKEY, so the
    archive is signed with the private exponent and opened with the public one.
    Verified against the standard Blowfish vectors and against two real
    encrypted archives (file count and body size come out exactly right, body
    size = file size - header - 20 byte SHA1 trailer).
    """
    rev = keysource[::-1]

    k1 = pow(int.from_bytes(rev[0:40], 'big'), RSA_PUB_EXP, RSA_MOD)
    k2 = pow(int.from_bytes(rev[40:80], 'big'), RSA_PUB_EXP, RSA_MOD)
    x = ((k1 << 312) + k2) & ((1 << 448) - 1)
    yield ("setkey/e/le", x.to_bytes(56, 'big')[::-1])

    # fallbacks, in case a differently built archive shows up
    k1 = pow(int.from_bytes(rev[0:40], 'big'), RSA_PRV_HEX, RSA_MOD)
    k2 = pow(int.from_bytes(rev[40:80], 'big'), RSA_PRV_HEX, RSA_MOD)
    x = ((k1 << 312) + k2) & ((1 << 448) - 1)
    yield ("setkey/d/le", x.to_bytes(56, 'big')[::-1])
    yield ("setkey/e/be", x.to_bytes(56, 'big'))

    a = pow(int.from_bytes(keysource[0:40], 'little'), RSA_PUB_EXP, RSA_MOD)
    b = pow(int.from_bytes(keysource[40:80], 'little'), RSA_PUB_EXP, RSA_MOD)
    bea = a.to_bytes(40, 'big')
    beb = b.to_bytes(40, 'big')
    yield ("dexoder/li/le39", (bea[1:][::-1] + beb[1:][::-1])[:56])


# ---------------------------------------------------------------------------
# file ids
# ---------------------------------------------------------------------------
_RA_ROTATE = True


def crc32_id(name):
    """RA2 / YR: plain CRC32 over the name padded up to a multiple of 4."""
    name = name.upper()
    l = len(name)
    if l & 3:
        pad = l - (l >> 2 << 2)
        name += chr(pad) + name[l - pad] * (3 - pad)
    return zlib.crc32(name.encode('latin-1')) & 0xFFFFFFFF


def rotate_id(name):
    """TD / RA: rotate the accumulator left one bit and add 4 characters."""
    name = name.upper()
    ident = 0
    i = 0
    l = len(name)
    while i < l:
        a = 0
        for _ in range(4):
            a >>= 8
            if i < l:
                a += ord(name[i]) << 24
            i += 1
        ident = (((ident << 1) | (ident >> 31)) & 0xFFFFFFFF) + a
        ident &= 0xFFFFFFFF
    return ident


GAME_ALGO = {
    "td": rotate_id, "ra": rotate_id, "ts": crc32_id, "ra2": crc32_id,
    "dune2": crc32_id, "dune2000": crc32_id,
}


def guess_game(path):
    base = os.path.basename(path).lower()
    return "ra2" if ("md" in base or base.startswith("ra2")) else "ra"


# ---------------------------------------------------------------------------
# name databases
# ---------------------------------------------------------------------------
GMD_ORDER = ["td", "ra", "ts", "ra2"]


def load_gmd(path):
    """global mix database.dat -> {game: {id: name}}"""
    data = open(path, 'rb').read()
    off = 0
    out = {}
    for game in GMD_ORDER:
        count = struct.unpack_from('<I', data, off)[0]
        off += 4
        table = {}
        for _ in range(count):
            end = data.index(b'\0', off)
            name = data[off:end].decode('latin-1')
            off = end + 1
            end = data.index(b'\0', off)
            off = end + 1
            table[GAME_ALGO[game](name)] = name
        out[game] = table
    return out


def load_lmd(blob, game):
    """local mix database.dat -> {id: name}"""
    algo = GAME_ALGO[game]
    if len(blob) < 52:
        return {}
    count = struct.unpack_from('<i', blob, 48)[0]
    off = 52
    table = {}
    for _ in range(max(count, 0)):
        end = blob.index(b'\0', off)
        name = blob[off:end].decode('latin-1')
        off = end + 1
        table[algo(name)] = name
    return table


# ---------------------------------------------------------------------------
# archive parsing
# ---------------------------------------------------------------------------
MIX_CHECKSUM = 0x00010000
MIX_ENCRYPTED = 0x00020000


class Mix(object):
    def __init__(self, path):
        self.path = path
        self.buf = open(path, 'rb').read()
        self.game = guess_game(path)
        self.flags = 0
        self.key_label = None
        self.entries = []          # (id, offset, size) offset relative to body
        self.body = 0
        self.body_size = 0
        self._parse()

    # -- helpers ----------------------------------------------------------
    def _try_index(self, first_block, rest, header_size, fc, body_size):
        """Validate a decrypted index; returns the entry list or None."""
        if not (0 < fc <= 20000):
            return None
        if body_size == 0 or body_size > len(self.buf):
            return None
        if header_size > len(self.buf):
            return None
        ind = first_block[6:8] + rest
        if len(ind) < fc * 12:
            return None
        entries = []
        for i in range(fc):
            ident, off, size = struct.unpack_from('<iII', ind, i * 12)
            if off + size > len(self.buf) or size > len(self.buf):
                return None
            entries.append((ident, off, size))
        covered = sum(1 for _, o, s in entries if o + s <= body_size + 8)
        if covered < fc * 9 // 10:
            return None
        return entries

    def _parse(self):
        buf = self.buf
        if len(buf) < 6:
            raise ValueError("too short")
        if buf[0:4] == b'MIX\x31':
            raise ValueError("Renegade mix, not supported")
        fc = struct.unpack_from('<H', buf, 0)[0]
        if fc:
            # plain format: 2B count + 4B body size + index
            self.entries = [struct.unpack_from('<iII', buf, 6 + i * 12)
                            for i in range(fc)]
            self.body = 6 + fc * 12
            self.body_size = struct.unpack_from('<I', buf, 2)[0]
            return

        self.flags = struct.unpack_from('<I', buf, 0)[0]
        if self.flags & MIX_ENCRYPTED:
            self._parse_encrypted()
        else:
            fc, body_size = struct.unpack_from('<HI', buf, 4)
            self.entries = [struct.unpack_from('<iII', buf, 10 + i * 12)
                            for i in range(fc)]
            self.body = 10 + fc * 12
            self.body_size = body_size

    def _parse_encrypted(self):
        buf = self.buf
        keysource = buf[4:84]
        cached = KEY_CACHE.get(keysource)
        if cached:
            candidates = [cached]
        else:
            candidates = _key_candidates(keysource)

        last = None
        for label, key in candidates:
            bf = Blowfish(key)
            first = bf.dec_block(buf[84:92])
            fc = struct.unpack_from('<H', first, 0)[0]
            body_size = struct.unpack_from('<I', first, 2)[0]
            blocks = -(-(fc * 12 - 2) // 8) if fc else 0
            if 84 + 8 + blocks * 8 > len(buf):
                last = label
                continue
            rest = b''.join(bf.dec_block(buf[92 + i * 8:100 + i * 8])
                            for i in range(blocks))
            header = 84 + 8 + blocks * 8
            entries = self._try_index(first, rest, header, fc, body_size)
            if entries is None:
                last = label
                continue
            KEY_CACHE[keysource] = (label, key)
            self.key_label = label
            self.entries = entries
            self.body = header
            self.body_size = body_size
            return
        raise ValueError("%s: no key derivation validated (last tried %s)"
                         % (self.path, last))

    # -- data -------------------------------------------------------------
    def raw(self, offset, size):
        return self.buf[self.body + offset:self.body + offset + size]

    def names(self, gmd):
        """id -> name, local database first, then the global one."""
        table = {}
        if gmd:
            table.update(gmd.get(self.game, {}))
        lmd_id = GAME_ALGO[self.game]("local mix database.dat")
        for ident, off, size in self.entries:
            if ident == lmd_id and 0 < size < self.body_size:
                table.update(load_lmd(self.raw(off, size), self.game))
                break
        return table

    def label(self, ident, table):
        name = table.get(ident & 0xFFFFFFFF)
        return name if name else "[id]%08X" % (ident & 0xFFFFFFFF)


# ---------------------------------------------------------------------------
# commands
# ---------------------------------------------------------------------------
def cmd_selftest():
    bf = Blowfish(b'\0' * 8)
    got = bf.enc_block(b'\0' * 8).hex().upper()
    print("blowfish key 0000000000000000 / block 0000000000000000")
    print("   got      %s" % got)
    print("   expected 4EF997456198DD78   %s" % ("OK" if got == "4EF997456198DD78"
                                                  else "MISMATCH"))
    _constants()
    print("pi constants: P[0]=%08X P[17]=%08X S[3][255]=%08X"
          % (_P[0], _P[17], _S[3][255]))
    print("   expected 243F6A88 8979FB1B 3AC372E6")
    print("rsa mod bitlen %d, private exponent bitlen %d"
          % (RSA_MOD.bit_length(), RSA_PRV.bit_length()))


def _open_gmd(args):
    path = None
    if '--gmd' in args:
        path = args[args.index('--gmd') + 1]
    if not path:
        for cand in ("global mix database.dat",
                     os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                  "global mix database.dat"),
                     r"D:\新建文件夹\VSProject\CCmix\test_files\global mix database.dat"):
            if os.path.isfile(cand):
                path = cand
                break
    return load_gmd(path) if path and os.path.isfile(path) else None


def _game(args, path):
    if '--game' in args:
        return args[args.index('--game') + 1].lower()
    return guess_game(path)


def _positional(args):
    out = []
    i = 0
    while i < len(args):
        if args[i] in ('--gmd', '--game'):
            i += 2
            continue
        if args[i] in ('--flat',):
            i += 1
            continue
        out.append(args[i])
        i += 1
    return out


def cmd_keyprobe(path):
    """Print what every key derivation makes of the first index block."""
    buf = open(path, 'rb').read(256)
    keysource = buf[4:84]
    print("%s: flags=0x%08X" % (path, struct.unpack_from('<I', buf, 0)[0]))
    for label, key in _key_candidates(keysource):
        bf = Blowfish(key)
        first = bf.dec_block(buf[84:92])
        fc, bs = struct.unpack_from('<HI', first, 0)
        print("  %-28s key=%s block=%s fc=%-6d body=%d"
              % (label, key[:8].hex(), first.hex(), fc, bs))


def cmd_keytest(path):
    mix = Mix(path)
    print("%s: entries=%d body=%d flags=0x%08X body_size=%d"
          % (os.path.basename(path), len(mix.entries), mix.body, mix.flags,
             mix.body_size))
    print("   key derivation: %s" % mix.key_label)


def cmd_list(path, args):
    mix = Mix(path)
    if '--game' in args:
        mix.game = _game(args, path)
    gmd = _open_gmd(args)
    table = mix.names(gmd)
    named = sum(1 for i, _, _ in mix.entries if (i & 0xFFFFFFFF) in table)
    print("%s: %d entries, body at %d, flags 0x%08X, game %s, key %s"
          % (path, len(mix.entries), mix.body, mix.flags, mix.game,
             mix.key_label))
    print("names resolved: %d/%d" % (named, len(mix.entries)))
    for ident, off, size in sorted(mix.entries, key=lambda e: e[1]):
        print("  %-32s %08X %10d %10d" % (mix.label(ident, table),
                                          ident & 0xFFFFFFFF, off, size))


def cmd_dump(path, name, outfile, args):
    mix = Mix(path)
    if '--game' in args:
        mix.game = _game(args, path)
    gmd = _open_gmd(args)
    table = mix.names(gmd)
    ident = None
    if name.lower().startswith('[id]'):
        ident = int(name[4:], 16)
    else:
        ident = GAME_ALGO[mix.game](name)
    for i, off, size in mix.entries:
        if (i & 0xFFFFFFFF) == (ident & 0xFFFFFFFF):
            data = mix.raw(off, size)
            with open(outfile, 'wb') as fh:
                fh.write(data)
            print("%s -> %s (%d bytes)" % (mix.label(i, table), outfile, size))
            return
    print("not found: %s (id %08X)" % (name, ident & 0xFFFFFFFF))


def _extract_one(mix, outdir, wants, flat, gmd, depth):
    table = mix.names(gmd)
    made = 0
    for ident, off, size in sorted(mix.entries, key=lambda e: e[1]):
        name = mix.label(ident, table)
        if wants and not any(w.lower() in name.lower() for w in wants):
            continue
        safe = name.replace('/', '_').replace('\\', '_')
        data = mix.raw(off, size)
        if not flat:
            target = os.path.join(outdir, safe)
        else:
            target = os.path.join(outdir, safe)
        with open(target, 'wb') as fh:
            fh.write(data)
        made += 1
        print("  %-34s %9d" % (safe, size))
        low = safe.lower()
        if depth > 0 and (low.endswith('.mix') or low.endswith('.mmx')):
            sub = os.path.join(outdir, os.path.splitext(safe)[0])
            if not flat:
                if not os.path.isdir(sub):
                    os.mkdir(sub)
                try:
                    child = Mix(target)
                    child.game = mix.game
                    print("  -> nested %s" % safe)
                    made += _extract_one(child, sub, [], flat, gmd, depth - 1)
                except Exception as exc:
                    print("  !! %s: %s" % (safe, exc))
    return made


def cmd_extract(path, outdir, wants, args):
    mix = Mix(path)
    if '--game' in args:
        mix.game = _game(args, path)
    flat = '--flat' in args
    gmd = _open_gmd(args)
    if not os.path.isdir(outdir):
        os.makedirs(outdir)
    print("extracting %s -> %s" % (path, outdir))
    made = _extract_one(mix, outdir, wants, flat, gmd, 1)
    print("done, %d files" % made)


def main(argv):
    if len(argv) < 2:
        print(__doc__)
        return 1
    cmd = argv[1]
    a = argv[2:]
    pos = _positional(a)
    if cmd == 'selftest':
        cmd_selftest()
    elif cmd == 'keytest':
        cmd_keytest(pos[0])
    elif cmd == 'keyprobe':
        cmd_keyprobe(pos[0])
    elif cmd == 'list':
        cmd_list(pos[0], a)
    elif cmd == 'dump':
        cmd_dump(pos[0], pos[1], pos[2], a)
    elif cmd == 'extract':
        cmd_extract(pos[0], pos[1], pos[2:], a)
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))

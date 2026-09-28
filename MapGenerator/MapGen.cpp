#include "pch.h"
#include "MapGen.h"

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cwchar>
#include <windows.h>

// ============================================================================
// Size interpolation tables (players 2-8, index 0-6)
// Source: 0x7ED634 / 0x7ED650 / 0x7ED66C / 0x7ED688
// ============================================================================
static const int kWmin[7] = { 70, 70, 70, 80, 90, 100, 100 };
static const int kWmax[7] = { 80, 80, 80, 90, 100, 110, 120 };
static const int kHmin[7] = { 70, 70, 70, 80, 90, 100, 100 };
static const int kHmax[7] = { 80, 80, 80, 90, 100, 110, 120 };

static const float kSizeClamp = 1.2f;
static const float kOneThird  = 1.0f / 3.0f;

// F2I64 (Game::F2I64 0x7C5F00, truncate toward zero) moved to MapGen.h - both
// this file and MapGenRiver.cpp use it.

// ============================================================================
// R250 Random Number Generator - exact replication of dst_ (0xABE890)
// ============================================================================

// Seed mixing tables (0x839644 / 0x839690, little-endian dwords)
static const uint32_t kSeedT1[4] =
    { 0xBAA96887u, 0x1E17D32Cu, 0x03BCDC3Cu, 0x0F33D1B2u };
static const uint32_t kSeedT2[5] =
    { 0x48AAD7E4u, 0x4B0F3B58u, 0xE874F0C3u, 0x6955C5A6u, 0x55A7CA46u };

// kUnitScale (Random_w scale, dbl_7ED898) moved to MapGen.h - both this file
// and MapGenRiver.cpp use it.

R250Random::R250Random()
    : index1_(0), index2_(103), gaussHave_(false), gaussSaved_(0.0)
{
    for (int i = 0; i < 250; ++i)
        buffer_[i] = 0;
}

// ---------------------------------------------------------------------------
// Seed (sub_65C6D0)
//
// Per-slot 4-round mixing. Assembly-verified details:
//   - v3 resets to the seed constant for every slot
//   - v4 chain: v4(slot) -> v8 -> v8 -> v8, written to buffer[slot]
//   - v3 chain: seed -> slot -> v8_1 -> v8_2 (previous v4 each round)
//   - hi = v7 SAR 16 (arithmetic), lo = v7 & 0xFFFF
//   - t = lo*lo + ~(hi*hi)   (imul/mul low 32 bits are identical)
//   - rot = (t SAR 16) | (t SHL 16)  - NOT a pure rotate when t < 0
//   - v8 = v3 ^ (hi*lo + (T2[n+1] ^ rot)), T2 indexed 1..4
// ---------------------------------------------------------------------------
void R250Random::Seed(uint32_t seed)
{
    for (int slot = 0; slot < 250; ++slot)
    {
        uint32_t v3 = seed;
        uint32_t v4 = (uint32_t)slot;
        for (int n = 0; n < 4; ++n)
        {
            uint32_t prev = v4;
            uint32_t v7 = v4 ^ kSeedT1[n];
            uint32_t hi = (uint32_t)((int32_t)v7 >> 16);  // sar
            uint32_t lo = v7 & 0xFFFFu;
            uint32_t hihi = hi * hi;
            uint32_t hilo = hi * lo;
            uint32_t lolo = lo * lo;
            uint32_t t = lolo + ~hihi;
            uint32_t rot = ((uint32_t)((int32_t)t >> 16)) | (t << 16);
            uint32_t v8 = v3 ^ (hilo + (kSeedT2[n + 1] ^ rot));
            v4 = v8;
            v3 = prev;
        }
        buffer_[slot] = v4;
    }
    index1_ = 0;    // this[1]
    index2_ = 103;  // this[2]
    // sub_598960 also resets the GaussState at 0xABDFB8 right after
    // seeding dst_: {flag byte = 0, saved = 0.0, fn = Random_w}
    gaussHave_ = false;
    gaussSaved_ = 0.0;
}

// ---------------------------------------------------------------------------
// Next (Randomizer::Random, 0x65C780)
//   buffer[index1] ^= buffer[index2]; result = buffer[index1];
//   both indices advance with wrap at 250.
//   (byte-size guard at this[0] is permanently 0 after seeding - skipped)
// ---------------------------------------------------------------------------
uint32_t R250Random::Next()
{
    buffer_[index1_] ^= buffer_[index2_];
    uint32_t result = buffer_[index1_];

    int i1 = index1_ + 1;
    int i2 = index2_ + 1;
    index1_ = i1;
    index2_ = i2;
    if (i1 >= 250)
        index1_ = 0;
    if (i2 >= 250)
        index2_ = 0;

    return result;
}

// ---------------------------------------------------------------------------
// RandomRanged (Randomizer::RandomRanged, 0x65C7E0)
//   - min == max -> min; else swap so min < max
//   - bit scan: n31 walks 30..0 (pre-decrement in asm), n31 = msb(nRange)
//   - mask = low (n31+1) bits; rejection: r = mask & Next() while r > range
//   - consumes a variable number of Next() calls
// ---------------------------------------------------------------------------
int R250Random::RandomRanged(int min, int max)
{
    if (min == max)
        return min;

    int nMin = min;
    int nMax = max;
    if (min > max)
    {
        nMin = max;
        nMax = min;
    }

    int nRange = nMax - nMin;

    int n31 = 31;
    if (nRange >= 0)
    {
        do
        {
            if (n31 <= 0)
                break;
            --n31;
        } while (((1 << n31) & nRange) == 0);
    }

    int mask = ~(-1 << (n31 + 1));
    int r = nRange + 1;
    while (r > nRange)
        r = (int)((uint32_t)mask & Next());

    return nMin + r;
}

// ---------------------------------------------------------------------------
// RandomFloatRange (sub_598030, fastcall: ecx=lo, edx=hi)
//   range = (double)(uint32)(hi - lo + 1)     [fild via zero-extended qword]
//   base  = (double)(uint32)lo
//   loop: F2I64(Next() * range * kUnitScale + base); reject if > hi (unsigned)
// ---------------------------------------------------------------------------
int R250Random::RandomFloatRange(int lo, int hi)
{
    double range = (double)(uint32_t)((uint32_t)hi - (uint32_t)lo + 1u);
    double base = (double)(uint32_t)lo;

    for (;;)
    {
        uint32_t r = Next();
        double x = (double)(uint64_t)r * range * kUnitScale + base;
        int64_t v = (int64_t)x;  // F2I64: truncate toward zero
        if ((uint32_t)v <= (uint32_t)hi)  // asm: cmp eax, esi / ja
            return (int)v;
    }
}

// ---------------------------------------------------------------------------
// Unit (Randomizer::Random_w, 0x598000)
//   fild(zero-extended Next()) then fmul dbl_7ED898
// ---------------------------------------------------------------------------
double R250Random::Unit()
{
    return (double)(uint64_t)Next() * kUnitScale;
}

// ---------------------------------------------------------------------------
// Chance25 (sub_599650 @ 0x59a4cc inline)
//   flag = Random() * kUnitScale < 0.25
//   (integer-equivalent: Next() <= 0x3FFFFFFF; no boundary ambiguity)
// ---------------------------------------------------------------------------
bool R250Random::Chance25()
{
    return Next() * kUnitScale < 0.25;
}

// ---------------------------------------------------------------------------
// Gaussian (sub_5980C0, Marsaglia polar method)
//
// Game state (GaussState at 0xABDFB8, reset in sub_598960):
//   +0x00 flag byte, +0x08 saved double, +0x10 fn ptr -> Random_w
// The uniform samples come from the SAME main RNG dst_ (via Random_w),
// each Unit() call consumes exactly one Next().
//
// asm-verified order: first call -> u, second call -> v;
// s = v*v + u*u; reject s >= 1.0, then reject s == 0.0;
// factor = sqrt((-ln(s) - ln(s)) / s); saved = factor*v, return factor*u.
// ---------------------------------------------------------------------------
double R250Random::Gaussian()
{
    if (gaussHave_)
    {
        gaussHave_ = false;
        return gaussSaved_;
    }

    double a = Unit();
    double b = Unit();
    double u = a + a - 1.0;
    double v = b + b - 1.0;
    double s = v * v + u * u;
    while (s >= 1.0 || s == 0.0)
    {
        a = Unit();
        b = Unit();
        u = a + a - 1.0;
        v = b + b - 1.0;
        s = v * v + u * u;
    }

    double lns = std::log(s);  // asm: fldln2 + fyl2x
    double factor = std::sqrt((-lns - lns) / s);

    gaussHave_ = true;
    gaussSaved_ = factor * v;
    return factor * u;
}

// ============================================================================
// RandomMapGenerator implementation
// ============================================================================

RandomMapGenerator::RandomMapGenerator()
    : iniLoaded_(false)
    , cellPool_(nullptr)
    , cellSlots_(nullptr)
    , slotRows_(0)
    , cellCount_(0)
    , workCells_(nullptr)
    , random25Flag_(false)
    , baseLevel_(4)
    , usedWaterCells_(0)
    , genCode_(0)
    , waterTileIndex_(-1)
    , shoreTileIndex_(-1)
    , waterCliffsIndex_(-1)
    , destroyableCliffsIndex_(-1)
    , cliffRampsIndex_(-1)
    , waterCavesIndex_(-1)
    , bridgeSetIndex_(-1)
    , woodBridgeSetIndex_(-1)
    , waterAmount_(0)
    , shorePieces_(-1)
    , currentBuildingType_(0)
{
    std::memset(&config_, 0, sizeof(config_));
    std::memset(&size_, 0, sizeof(size_));
    std::memset(shoreAnchor_, 0, sizeof(shoreAnchor_));
    // ReadINI leaves every tile-family global at -1 before filling it.
    for (int i = 0; i < 4; ++i)
        waterFamily4Base_[i] = -1;
    settings_.SetDefaults();
}

RandomMapGenerator::~RandomMapGenerator()
{
    delete[] cellPool_;
    delete[] cellSlots_;
    delete[] workCells_;
}

// ---------------------------------------------------------------------------
// CalcMapSize (replicates 0x599665 - 0x599748)
//
//   i = clamp(playerCount - 2, 0, 6)
//   wFrac = hFrac = sizeSlider / 3.0
//   if LandType != Inland and != Mountainous: clamp both to 1.2
//   W = F2I64(Wmin[i]*(1-wFrac) + Wmax[i]*wFrac)   (visible size)
//   H = F2I64(Hmin[i]*(1-hFrac) + Hmax[i]*hFrac)
//   W' = W + 4, H' = H + 12  (MapRect, sub_42AC00)
//   workSide = W' + H' + 1  (dword_89C2DC)
// ---------------------------------------------------------------------------
MapSizeResult RandomMapGenerator::CalcMapSize(const MapGenConfig& cfg) const
{
    MapSizeResult result = {};

    int playerIdx = cfg.playerCount - 2;
    if (playerIdx < 0) playerIdx = 0;
    if (playerIdx > 6) playerIdx = 6;

    float wFrac = (float)cfg.sizeSlider * kOneThird;
    float hFrac = (float)cfg.sizeSlider * kOneThird;

    LandType lt = cfg.landType;
    if (lt != LandType::Inland && lt != LandType::Mountainous)
    {
        if (wFrac > kSizeClamp) wFrac = kSizeClamp;
        if (hFrac > kSizeClamp) hFrac = kSizeClamp;
    }

    float w = kWmin[playerIdx] * (1.0f - wFrac) + kWmax[playerIdx] * wFrac;
    float h = kHmin[playerIdx] * (1.0f - hFrac) + kHmax[playerIdx] * hFrac;

    result.width     = F2I64(w);
    result.height    = F2I64(h);
    result.mapWidth  = result.width + 4;
    result.mapHeight = result.height + 12;
    result.workSide  = result.mapWidth + result.mapHeight + 1;

    return result;
}

// ---------------------------------------------------------------------------
// InitCells (MapClass::CreateEmptyMap + cell reset 0x599e86 - 0x599eaa)
//
// Diamond existence: W' < x+y <= W'+2H' and |x-y| < W' (CellExists).
// Slot array: 512-stride rows, nullptr outside the diamond - this is the
// sentinel the CellIterator probes to terminate enumeration.
// Cell reset: SlopeIndex=0, Level=4, IsoTileTypeIndex=0, Height=0,
//             OverlayTypeIndex=-1, OverlayData=0.
// ---------------------------------------------------------------------------
void RandomMapGenerator::InitCells()
{
    delete[] cellPool_;
    delete[] cellSlots_;
    cellPool_ = nullptr;
    cellSlots_ = nullptr;
    slotRows_ = 0;
    cellCount_ = 0;

    // Rows cover every diagonal the iterator can touch (incl. the
    // out-of-diamond probe cell that terminates iteration)
    slotRows_ = size_.mapWidth + size_.mapHeight + 1;
    cellSlots_ = new MapCell*[slotRows_ * 512];
    std::memset(cellSlots_, 0, sizeof(MapCell*) * slotRows_ * 512);

    // x spans [1, W'+H'-1] inside the diamond (x = 0 has no solution)
    int maxX = size_.mapWidth + size_.mapHeight - 1;

    for (int y = 0; y < slotRows_; ++y)
        for (int x = 0; x <= maxX; ++x)
            if (CellExists(x, y))
                ++cellCount_;

    cellPool_ = new MapCell[cellCount_];

    int idx = 0;
    for (int y = 0; y < slotRows_; ++y)
    {
        for (int x = 0; x <= maxX; ++x)
        {
            if (!CellExists(x, y))
                continue;
            MapCell& cell = cellPool_[idx];
            cell.MapCoords = x | (y << 16);
            cell.Level = baseLevel_;
            cell.IsoTileTypeIndex = 0;
            cell.SlopeIndex = 0;
            cell.Height = 0;
            cell.OverlayTypeIndex = -1;
            cell.OverlayData = 0;
            cell.AltFlags = 0;
            cellSlots_[512 * y + x] = &cellPool_[idx];
            ++idx;
        }
    }
}

// ---------------------------------------------------------------------------
// InitWorkArray (0x59a30a - 0x59a37f)
//   80 bytes per cell, workSide * workSide cells.
//   WorkCell ctor: bytes 64..67 = -1 (data[16]), byte 74 = 1.
// ---------------------------------------------------------------------------
void RandomMapGenerator::InitWorkArray()
{
    delete[] workCells_;
    workCells_ = new WorkCell[size_.workSide * size_.workSide];
}

// ---------------------------------------------------------------------------
// FillWorkCoords (0x59a385 - 0x59a3dc)
//   Enumerate cells in iterator (diagonal) order, write MapCoords into
//   workArray[x + workSide * y].
// ---------------------------------------------------------------------------
void RandomMapGenerator::FillWorkCoords()
{
    if (!workCells_ || !cellSlots_)
        return;

    CellIterator it;
    it.Reset(cellSlots_, size_.mapWidth);
    while (MapCell* cell = it.Next())
    {
        int x = cell->MapCoords & 0xFFFF;
        int y = (uint32_t)cell->MapCoords >> 16;
        workCells_[x + size_.workSide * y].MapCoords() = cell->MapCoords;
    }
}

// ---------------------------------------------------------------------------
// GenerateMapBody - RNG-relevant core of sub_599650 / sub_598960
//
//   1. rng_.Seed(seed)         (qmemcpy(&dst_, sub_65C6D0(v39, this[29])))
//                              + GaussState reset at 0xABDFB8 (in Seed)
//   2. ReInitMapData()         (sub_5981F0, no RNG consumption)
//   3. CalcMapSize()           (0x599665 - 0x599748)
//   4. InitCells()             (CreateEmptyMap semantics)
//   5. InitWorkArray()         (0x59a30a - 0x59a37f)
//   6. FillWorkCoords()        (0x59a385 - 0x59a3dc)
//   7. random25Flag_           (0x59a4cc, exactly ONE Random() call)
//
// Verified via dst_ xrefs: no other RNG consumer runs between the seeding
// and sub_59A6C0 terrain generation.
// ---------------------------------------------------------------------------
bool RandomMapGenerator::GenerateMapBody(const MapGenConfig& cfg)
{
    config_ = cfg;

    // Water amount (this[19]): rolled by the caller, same as vanilla rolls
    // it in the dialog layer (sub_597260) before generation starts.
    waterAmount_ = cfg.waterAmount;

    rng_.Seed(cfg.randomSeed);

    ReInitMapData();

    size_ = CalcMapSize(cfg);
    if (size_.width <= 0 || size_.height <= 0)
        return false;

    baseLevel_ = 4;
    usedWaterCells_ = 0;    // RMG this[193]: per-map river/lake budget counter
    LoadTheaterTiles(cfg.theater);   // IsometricTileTypeClass::ReadINI [General]
    InitCells();
    InitWorkArray();
    FillWorkCoords();

    random25Flag_ = rng_.Chance25();

    return true;
}

// ---------------------------------------------------------------------------
// GenerateTerrain - sub_59A6C0 segments 1 + 2
//
// Segment 1 (0x59a724 - 0x59a738): flood every diamond cell with water.
//   sub_578350(&MouseClass::Instance);            // reset iterator
//   for ( i = CellIteratorNext(); i; i = CellIteratorNext() )
//     i->IsoTileTypeIndex = nIdx;                 // WaterSet base tile
//
// Segment 2 (0x59a6f6 - 0x59a718): dispatch by this[15] (LandType):
//   0 -> sub_59AD10 (Archipelago)
//   1 -> sub_59AFA0 (Continent)
//   2 -> sub_59B200 (TeamContinent)
// LandType 3/4 (Inland/Mountainous) never reach sub_59A6C0 in vanilla
// (sub_598960 routes them to sub_59C580) and fall through, mirrored here.
//
// Segments 3-6 of sub_59A6C0 are not implemented.
// ---------------------------------------------------------------------------
void RandomMapGenerator::GenerateTerrain()
{
    // Segment 1: flood with water
    CellIterator it;
    it.Reset(cellSlots_, size_.mapWidth);
    while (MapCell* cell = it.Next())
        cell->IsoTileTypeIndex = waterTileIndex_;

    // Segment 2: land type dispatch (generator bodies pending)
    switch (config_.landType)
    {
    case LandType::Archipelago:
        GenerateArchipelago();
        break;
    case LandType::Continent:
        GenerateContinent();
        break;
    case LandType::TeamContinent:
        GenerateTeamContinent();
        break;
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// ClearWorkOccupancy - common generator prologue
//
// Vanilla (e.g. sub_59AD10 @ 0x59ad5e, sub_59AFA0 @ 0x59b043,
// sub_59B200 @ 0x59b063):
//   sub_578350(&MouseClass::Instance);
//   for ( i = CellIteratorNext(); i; i = CellIteratorNext() )
//     *(dword_ABED10 + 20 * i->MapCoords
//       + 20 * dword_89C2DC * HIWORD(i->MapCoords) + 15) = 0;
// (dword +15 = byte 60 = work cell data[15], the occupancy mark)
// ---------------------------------------------------------------------------
void RandomMapGenerator::ClearWorkOccupancy()
{
    CellIterator it;
    it.Reset(cellSlots_, size_.mapWidth);
    while (MapCell* cell = it.Next())
    {
        int x = cell->MapCoords & 0xFFFF;
        int y = (uint32_t)cell->MapCoords >> 16;
        workCells_[x + size_.workSide * y].data[15] = 0;
    }
}

// ---------------------------------------------------------------------------
// Land type generators - stubs, bodies pending
// ---------------------------------------------------------------------------

// sub_59AD10 (Archipelago): split VisibleRect into blocks via sub_59A8F0,
// per block: seed = block center (diamond coords), GrowPatch with
// step 0.25 / mode 0 / rect bounds, retry <= 10, then advance block.
void RandomMapGenerator::GenerateArchipelago()
{
    // TODO: replicate sub_59AD10 (0x59AD10)
}

// sub_59AFA0 (Continent): single ellipse = VisibleRect inset by 1,
// seed starts at map center, then nearest unoccupied cell to center;
// GrowPatch with step 0.75 / mode 1 / ellipse bounds, cap 100 patches.
void RandomMapGenerator::GenerateContinent()
{
    // TODO: replicate sub_59AFA0 (0x59AFA0)
}

// sub_59B200 (TeamContinent): coin-flip horizontal/vertical split into two
// halves, per half: seed starts at half center, then weighted-nearest
// unoccupied cell inside half rect + ellipse; step 0.75 / mode 1,
// shared cap 100 patches.
void RandomMapGenerator::GenerateTeamContinent()
{
    // TODO: replicate sub_59B200 (0x59B200)
}

// ---------------------------------------------------------------------------
// GrowPatch - sub_59BBC0 organic patch growth engine - stub, body pending.
// Full annotated walkthrough: sub_59BBC0_注释.md.
// ---------------------------------------------------------------------------
int RandomMapGenerator::GrowPatch(int /*area*/, const MapRectTag* /*bounds*/,
                                  int /*seedXY*/, int /*boundsMode*/,
                                  int /*centerXY*/, double /*step*/,
                                  int /*priorityMode*/)
{
    // TODO: replicate sub_59BBC0 (0x59BBC0)
    return 0;
}

// ---------------------------------------------------------------------------
// GenerateSpecialTerrain - sub_59C580 (LandType 3/4, Inland / Mountainous)
//
// Full annotated walkthrough: sub_59C580_注释.md (flowchart §11).
//
// Implemented: prologue (preparation, 0x59c58e - 0x59c59b) + river stage
//              dispatch loop (0x59c5ac - 0x59c5db) + lake stage
//              (0x59c5e8 - 0x59c60b, up to 10 GenerateLake tries).
// GenerateRiver / GenerateDelta / GenerateLake are all implemented, so this
// whole special-terrain path (sub_59C580) now runs end to end.
// ---------------------------------------------------------------------------
void RandomMapGenerator::GenerateSpecialTerrain()
{
    // [Preparation] generation-code increment (0x59c58e - 0x59c59b,
    // ++this[194] / ++genCode_). Every cell carved by this special-water
    // pass gets stamped with the new code (work-cell generation mark,
    // byte offset 56). On any failure the rollback pass identifies this
    // attempt's cells exactly by "generation mark == current code" and
    // clears them (rollback details: doc §5.9 / §6.7). The code is 0 on
    // entry: LandType 3/4 never runs sub_59A6C0 (which sets it to 1), so
    // after the increment the current code is 1, distinct from the
    // map-wide 0 (free land).
    ++genCode_;

    // ---- Stage 1: river (0x59c5ac - 0x59c5db) ----
    // Enabled only when the land type is Inland or Mountainous (this[15]
    // is 3 or 4; cached into a register at entry) and water amount > 20
    // (this[19]). Up to 10 attempts, first success stops (at most one
    // main river per map); on success the generation code is incremented
    // again, freeing a fresh code for the next water body (lakes).
    int landType = static_cast<int>(config_.landType);          // 0x59c594 mov eax,[esi+3Ch]
    if ((landType == 3 || landType == 4) && waterAmount_ > 20)  // 0x59c598/0x59c5a3/0x59c5a8
    {
        for (int i = 0; i < 10; ++i)                            // 0x59c5b5 max 10 tries
        {
            // Zero the start before each attempt -> (0,0) = automatic
            // mode (random edge start)
            int startXY = 0;                                    // 0x59c5c1/0x59c5c6 v6=v7=0
            if (GenerateRiver(&startXY, 0.0, false))            // 0x59c5cb top-level call
            {
                ++genCode_;                                     // 0x59c5db
                break;                                          // 0x59c5db
            }
        }
    }
    // ---- Stage 2: independent lakes (0x59c5e8 - 0x59c60b) ----
    // NOT gated by land type or water amount: the lake body checks its own
    // budget against the used-water counter inside sub_59C920 (§6.1). Up to 10
    // attempts, each with seed (0,0) so the callee samples a point itself; the
    // first success bumps the generation code (isolating a later rollback) and
    // ends the stage. Vanilla's sub_59C580 returns 1 on a successful lake and 0
    // when all ten fail - the caller here ignores it, so this stays void.
    //
    // The stage itself consumes no RNG: seed selection and the rest happen
    // inside GenerateLake.
    for (int i = 0; i < 10; ++i)                                // 0x59c5e8 max 10 tries
    {
        int lakeSeed = 0;                                       // 0x59c5f5 (0,0) = automatic
        if (GenerateLake(&lakeSeed))                            // 0x59c5fb
        {
            ++genCode_;                                         // 0x59c605
            return;                                             // 0x59c60b return 1
        }
    }
}

// ---------------------------------------------------------------------------
// Tile predicates - sub_485060 / sub_486380
//
//   IsWaterTile       sub_485060: IsoTileTypeIndex in [nIdx, nIdx + 14)
//   IsPlaceholderTile sub_486380: IsoTileTypeIndex is 0 or 0xFFFF
//
// nIdx is the WaterSet base tile (game global 0xAA0738 = waterTileIndex_).
// ---------------------------------------------------------------------------
bool RandomMapGenerator::IsWaterTile(const MapCell* cell) const
{
    const int tile = cell->IsoTileTypeIndex;
    return tile >= waterTileIndex_ && tile < waterTileIndex_ + 14;
}

bool RandomMapGenerator::IsPlaceholderTile(const MapCell* cell) const
{
    const int tile = cell->IsoTileTypeIndex;
    return tile == 0 || tile == 0xFFFF;
}

// ---------------------------------------------------------------------------
// CellAt - MapClass::GetCellAt_MapCrd (0x5657AF).
//
// The slot index is X + (Y << 9); out-of-range indices and null slots fall
// back to MapClass::InvalidCell with MapCoords stamped with the requested
// coords (here invalidCell_). Every in-diamond coordinate resolves to a real
// cell, so the sentinel is only ever produced for coordinates outside the
// diamond.
// ---------------------------------------------------------------------------
MapCell* RandomMapGenerator::CellAt(int x, int y)
{
    const int index = x + (y << 9);
    if (index >= 0 && index < slotRows_ * 512 && cellSlots_[index])
        return cellSlots_[index];

    invalidCell_.MapCoords = (static_cast<int>(static_cast<int16_t>(x)) & 0xFFFF)
                           | (static_cast<int>(static_cast<int16_t>(y)) << 16);
    return &invalidCell_;
}

// ---------------------------------------------------------------------------
// RawSlot - Cells.Items[index] as read by the TileNeighbourMask scan.
//
// Unlike CellAt there is no InvalidCell fallback: an out-of-range index or a
// null slot yields nullptr, which the mask scan reads as "no neighbour".
// ---------------------------------------------------------------------------
MapCell* RandomMapGenerator::RawSlot(int index)
{
    if (index < 0 || index >= slotRows_ * 512)
        return nullptr;
    return cellSlots_[index];
}

// ---------------------------------------------------------------------------
// GetNeighbourCell - CellClass::GetNeighbourCell (0x481810).
//
// Adds Neighbours[facing & 7] to the cell's MapCoords (16-bit adds, matching
// the vanilla CellStruct arithmetic) and looks the result up with CellAt.
//   [0] (0,-1)  [1] (1,-1)  [2] (1,0)  [3] (1,1)
//   [4] (0, 1)  [5] (-1,1)  [6] (-1,0) [7] (-1,-1)
// ---------------------------------------------------------------------------
MapCell* RandomMapGenerator::GetNeighbourCell(const MapCell* cell, int facing)
{
    static const int16_t kDirX[8] = { 0,  1,  1,  1,  0, -1, -1, -1 };
    static const int16_t kDirY[8] = {-1, -1,  0,  1,  1,  1,  0, -1 };

    const int16_t x = static_cast<int16_t>(cell->MapCoords & 0xFFFF) + kDirX[facing & 7];
    const int16_t y = static_cast<int16_t>((uint32_t)cell->MapCoords >> 16) + kDirY[facing & 7];
    return CellAt(x, y);
}

// ============================================================================
// RMGSettings implementation
// ============================================================================

// ---------------------------------------------------------------------------
// SetDefaults - vanilla RA2 YR RMGMD.INI contents
// (vanilla always ships the file; standalone build uses it as fallback)
// ---------------------------------------------------------------------------
void RMGSettings::SetDefaults()
{
    MinTiberium = 900;    // RMGMinimumTiberium
    MaxTiberium = 1050;   // RMGMaximumTiberium
    MaxTrees    = 600;    // MaxTrees

    // by time of day: (morning, day, dusk, night)
    LevelLightSettings    = { 3,   3,   3,   3   };

    // by time of day: range 0 (black) to 100 (normal brightness)
    TemperateAmbientLight = { 75,  100, 75,  35  };
    SnowAmbientLight      = { 75,  100, 75,  55  };
    TemperateAmbientRed   = { 109, 108, 71,  51  };
    TemperateAmbientGreen = { 80,  94,  81,  46  };
    TemperateAmbientBlue  = { 49,  68,  119, 141 };
    SnowAmbientRed        = { 112, 99,  106, 76  };
    SnowAmbientGreen      = { 80,  104, 107, 74  };
    SnowAmbientBlue       = { 133, 107, 154, 118 };

    // by land type: (archipelago, continent, team continent, inland, mountainous)
    VegetationMinimums    = { 60,  60,  60,  60,  60  };
    VegetationMaximums    = { 100, 100, 100, 100, 100 };

    // by time of day: valid building INI names
    TemperateOrePatchLamps = { "TEMMORLAMP", "TEMDAYLAMP", "TEMDUSLAMP", "TEMNITLAMP" };
    SnowOrePatchLamps      = { "SNOMORLAMP", "SNODAYLAMP", "SNODUSLAMP", "SNONITLAMP" };
}

// Safe index helpers (empty group -> 0, out-of-range -> last element)
static int ListAt(const std::vector<int>& v, int i)
{
    if (v.empty()) return 0;
    if (i < 0) i = 0;
    if (i >= (int)v.size()) i = (int)v.size() - 1;
    return v[i];
}

int RMGSettings::LevelLight(int timeOfDay) const
{
    return ListAt(LevelLightSettings, timeOfDay);
}

int RMGSettings::AmbientLight(int theater, int timeOfDay) const
{
    const std::vector<int>& v = theater ? SnowAmbientLight : TemperateAmbientLight;
    return ListAt(v, timeOfDay);
}

int RMGSettings::VegetationMin(int landType) const
{
    return ListAt(VegetationMinimums, landType);
}

int RMGSettings::VegetationMax(int landType) const
{
    return ListAt(VegetationMaximums, landType);
}

// ============================================================================
// sub_5981F0 replication - re-initialize map data from RMGMD.INI
// ============================================================================

// ---------------------------------------------------------------------------
// ReadIntList - comma-separated int list (replicates sub_475D70)
//   - 512-byte read buffer
//   - strtok by "," then atoi per token
//   - empty token terminates the loop (vanilla: "if (!*token) break")
//   - key absent -> list stays empty (vanilla "not read" branch)
// ---------------------------------------------------------------------------
static void ReadIntList(const char* path, const char* key, std::vector<int>& out)
{
    out.clear();
    char buffer[512];
    DWORD n = GetPrivateProfileStringA("General", key, "", buffer, 512, path);
    if (n == 0)
        return;

    char* next = nullptr;
    for (char* tok = strtok_s(buffer, ",", &next); tok; tok = strtok_s(nullptr, ",", &next))
    {
        if (!*tok)
            break;
        out.push_back(atoi(tok));
    }
}

// ---------------------------------------------------------------------------
// ReadNameList - comma-separated building name list (OrePatchLamps part of
// sub_5981F0)
//   - 128-byte read buffer (vanilla pBuffer_[128])
//   - list is cleared in both branches (read / not read)
//   - vanilla resolves each token via BuildingTypeClass::Find and skips
//     unknown names; standalone build keeps the raw names
// ---------------------------------------------------------------------------
static void ReadNameList(const char* path, const char* key, std::vector<std::string>& out)
{
    out.clear();
    char buffer[128];
    DWORD n = GetPrivateProfileStringA("General", key, "", buffer, 128, path);
    if (n == 0)
        return;

    char* next = nullptr;
    for (char* tok = strtok_s(buffer, ",", &next); tok; tok = strtok_s(nullptr, ",", &next))
    {
        if (!*tok)
            break;
        out.push_back(tok);
    }
}

// ---------------------------------------------------------------------------
// ReInitMapData (replicates sub_5981F0, called from sub_599650 at 0x599685)
//
// Vanilla flow:
//   1. Open RMGMD.INI from the game directory (CCFileClass + CCINIClass)
//   2. Unconditionally clear the setting groups
//   3. Read [General] keys in this exact order:
//        RMGMinimumTiberium / RMGMaximumTiberium  (int, default = current value)
//        RMGLevelLightSettings, RMGVegetationMinimums, RMGVegetationMaximums,
//        TemperateAmbientLight, SnowAmbientLight, TemperateAmbientRed,
//        TemperateAmbientGreen, TemperateAmbientBlue, SnowAmbientRed,
//        SnowAmbientGreen, SnowAmbientBlue   (comma-separated int lists)
//        MaxTrees   (int, default = current value)
//        TemperateOrePatchLamps / SnowOrePatchLamps  (name lists)
//   4. Destroy the INI object and close the file
//
// Differences for the standalone build:
//   - INI parsing uses Win32 GetPrivateProfile* instead of CCINIClass
//   - Vanilla always ships RMGMD.INI next to the exe; when the file is
//     missing here the built-in vanilla defaults are kept instead
// ---------------------------------------------------------------------------
bool RandomMapGenerator::ReInitMapData()
{
    // RMGMD.INI next to the executable (vanilla: game directory)
    wchar_t wdir[MAX_PATH];
    GetModuleFileNameW(nullptr, wdir, MAX_PATH);
    wchar_t* slash = wcsrchr(wdir, L'\\');
    if (slash)
        slash[1] = L'\0';
    wchar_t wpath[MAX_PATH];
    swprintf_s(wpath, L"%sRMGMD.INI", wdir);

    if (GetFileAttributesW(wpath) == INVALID_FILE_ATTRIBUTES)
    {
        // File missing: keep built-in defaults (vanilla never hits this path)
        iniLoaded_ = false;
        return false;
    }

    char path[MAX_PATH];
    WideCharToMultiByte(CP_ACP, 0, wpath, -1, path, MAX_PATH, nullptr, nullptr);

    settings_.LevelLightSettings.clear();
    settings_.TemperateAmbientLight.clear();
    settings_.SnowAmbientLight.clear();
    settings_.TemperateAmbientRed.clear();
    settings_.TemperateAmbientGreen.clear();
    settings_.TemperateAmbientBlue.clear();
    settings_.SnowAmbientRed.clear();
    settings_.SnowAmbientGreen.clear();
    settings_.SnowAmbientBlue.clear();
    settings_.VegetationMinimums.clear();
    settings_.VegetationMaximums.clear();
    settings_.TemperateOrePatchLamps.clear();
    settings_.SnowOrePatchLamps.clear();

    settings_.MinTiberium = (int)GetPrivateProfileIntA(
        "General", "RMGMinimumTiberium", (UINT)settings_.MinTiberium, path);
    settings_.MaxTiberium = (int)GetPrivateProfileIntA(
        "General", "RMGMaximumTiberium", (UINT)settings_.MaxTiberium, path);

    ReadIntList(path, "RMGLevelLightSettings",    settings_.LevelLightSettings);
    ReadIntList(path, "RMGVegetationMinimums",    settings_.VegetationMinimums);
    ReadIntList(path, "RMGVegetationMaximums",    settings_.VegetationMaximums);
    ReadIntList(path, "TemperateAmbientLight",    settings_.TemperateAmbientLight);
    ReadIntList(path, "SnowAmbientLight",         settings_.SnowAmbientLight);
    ReadIntList(path, "TemperateAmbientRed",      settings_.TemperateAmbientRed);
    ReadIntList(path, "TemperateAmbientGreen",    settings_.TemperateAmbientGreen);
    ReadIntList(path, "TemperateAmbientBlue",     settings_.TemperateAmbientBlue);
    ReadIntList(path, "SnowAmbientRed",           settings_.SnowAmbientRed);
    ReadIntList(path, "SnowAmbientGreen",         settings_.SnowAmbientGreen);
    ReadIntList(path, "SnowAmbientBlue",          settings_.SnowAmbientBlue);

    settings_.MaxTrees = (int)GetPrivateProfileIntA(
        "General", "MaxTrees", (UINT)settings_.MaxTrees, path);

    ReadNameList(path, "TemperateOrePatchLamps", settings_.TemperateOrePatchLamps);
    ReadNameList(path, "SnowOrePatchLamps",      settings_.SnowOrePatchLamps);

    iniLoaded_ = true;
    return true;
}

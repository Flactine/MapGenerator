#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

// ============================================================================
// Shared numeric helpers (used by MapGen.cpp and MapGenRiver.cpp)
//
// F2I64 - Game::F2I64 (0x7C5F00, RC=3): truncate toward zero. The double
//   overload must not narrow through float first - river coordinates live on
//   the x87 stack and the game truncates the st0 value directly.
// kUnitScale - Random_w scale (dbl_7ED898): 2^-32 * (1 + 2^-32), bits
//   0x3DF0000000100000. NOT 1/2^32 and NOT the nearest double of 1/(2^32-1) -
//   do not "fix".
// ============================================================================
inline int F2I64(float v)  { return (int)v; }
inline int F2I64(double v) { return (int)v; }
constexpr double kUnitScale = 2.3283064370807974e-10;

// ============================================================================
// LandType - 5 terrain layouts from RA2 RMG
//   0 = Archipelago
//   1 = Continent
//   2 = Team Continent
//   3 = Inland (special, no 1.2 clamp)
//   4 = Mountainous (special, no 1.2 clamp)
// ============================================================================
enum class LandType : int
{
    Archipelago   = 0,
    Continent     = 1,
    TeamContinent = 2,
    Inland        = 3,
    Mountainous   = 4,
};

// ============================================================================
// Theater type
// ============================================================================
enum class TheaterType : int
{
    Temperate = 0,
    Snow      = 1,
};

// ============================================================================
// Time of day
// ============================================================================
enum class TimeOfDay : int
{
    Morning   = 0,
    Afternoon = 1,
    Dusk      = 2,
    Night     = 3,
};

// ============================================================================
// Rect (RectangleStruct)
// ============================================================================
struct MapRectTag
{
    int X;
    int Y;
    int Width;
    int Height;
};

// ============================================================================
// CellStruct - packed cell coordinate (YRpp GeneralStructures.h)
//   struct CellStruct { __int16 X; __int16 Y; };   // 4 bytes
// Also the element type of the foundation-preview lists, which are
// terminated by the sentinel (0x7FFF, 0x7FFF).
// ============================================================================
struct CellStruct
{
    int16_t X;
    int16_t Y;
};

// ============================================================================
// FoundationPreviewState - the DisplayClass foundation-preview fields
// (YRpp DisplayClass.h) that the water-smoothing passes read and write.
//
//   vanilla offset   YRpp member name                    here
//   +0x1174          CurrentFoundation_CenterCell        CenterCell
//   +0x1178          CurrentFoundation_TopLeftOffset     TopLeftOffset
//   +0x117C          CurrentFoundation_Data              Data
//
// Vanilla keeps these in the process-global MouseClass::Instance. The
// generator owns its own copy because two steps of SmoothWaterBody touch it:
//   ResetPreviewState (sub_4A8BF0) clears it, and
//   SelectShoreTile    (sub_57ACF0) passes it to sub_4A91B0.
// Data points at a CellStruct list terminated by the (0x7FFF, 0x7FFF)
// sentinel; the list is limited to 120 entries (0x1E0 bytes).
// ============================================================================
struct FoundationPreviewState
{
    CellStruct  CenterCell;
    CellStruct  TopLeftOffset;
    CellStruct* Data;

    FoundationPreviewState()
        : CenterCell{0, 0}, TopLeftOffset{0, 0}, Data(nullptr)
    {}
};

// ============================================================================
// R250 Random Number Generator
//
// Exact replication of the game's global Randomizer (dst_ at 0xABE890):
//   - Seed  : sub_65C6D0 (4-round constant mixing per buffer slot)
//   - Next  : Randomizer::Random  (0x65C780, dual-pointer XOR feedback)
//   - Range : Randomizer::RandomRanged (0x65C7E0, bitmask rejection sampling)
//   - Unit  : Randomizer::Random_w (0x598000, Next() * 1/(2^32-1))
//   - Gauss : sub_5980C0 (Marsaglia polar method, second value cached)
// ============================================================================
class R250Random
{
public:
    R250Random();

    // Seed the generator (exact replication of sub_65C6D0)
    void Seed(uint32_t seed);

    // Generate next 32-bit random integer (Randomizer::Random, 0x65C780)
    uint32_t Next();

    // Random integer in [min, max] (Randomizer::RandomRanged, 0x65C7E0).
    // Bitmask rejection sampling - consumes a variable number of Next() calls.
    int RandomRanged(int lo, int hi);

    // Random integer in [lo, hi] (sub_598030, float scaling + upper rejection)
    int RandomFloatRange(int lo, int hi);

    // Uniform double in [0, 1] (Randomizer::Random_w, 0x598000)
    double Unit();

    // 25% chance boolean (sub_599650: Random() * 2.328306437080797e-10 < 0.25)
    bool Chance25();

    // Normal-distributed double (sub_5980C0, Marsaglia polar method)
    double Gaussian();

private:
    uint32_t buffer_[250];
    int      index1_;
    int      index2_;
    bool     gaussHave_;    // sub_5980C0 cached flag
    double   gaussSaved_;   // sub_5980C0 cached second value
};

// MapCell::AltFlags bits - subset of YRpp AltCellFlags (GeneralDefinitions.h)
// that the generation path actually touches.
enum AltCellFlags
{
    // Set while a cell is covered by the building foundation currently being
    // previewed, cleared when the preview moves away (sub_4A95A0).
    AltCellFlags_ContainsBuilding = 0x2,
};

// ============================================================================
// MapCell - simplified CellClass (only fields used during generation)
//
// Cell reset loop of sub_599650 (0x599e86):
//   SlopeIndex = 0, Level = 4, IsoTileTypeIndex = 0, Height = 0,
//   OverlayTypeIndex = -1, OverlayData = 0
//
// AltFlags (CellClass::AltFlags) is not part of that reset loop - the game
// zeroes it when the map is created - but it is carried here because the
// foundation-preview bookkeeping (sub_4A95A0) writes it.
// ============================================================================
struct MapCell
{
    int  MapCoords;          // packed: low 16 bits = X, high 16 bits = Y
    int  Level;
    int  IsoTileTypeIndex;
    int  SlopeIndex;
    int  Height;
    int  OverlayTypeIndex;
    int  OverlayData;
    int  AltFlags;           // AltCellFlags bits (ContainsBuilding)

    MapCell()
        : MapCoords(0), Level(4), IsoTileTypeIndex(0), SlopeIndex(0)
        , Height(0), OverlayTypeIndex(-1), OverlayData(0), AltFlags(0)
    {}
};

// ============================================================================
// WorkCell - 80-byte work array cell (global dword_ABED10)
//
// Byte-level init from sub_599650 (0x59a321 - 0x59a376):
//   bytes  0..3   = 0     (MapCoords, two zero words)
//   bytes  4..7   = 0     (uninitialized in game; zeroed here)
//   bytes  8..63  = 0
//   bytes 64..67  = -1    (int32, data[16])
//   bytes 68..73  = 0
//   byte  74      = 1     (flags byte)
//   bytes 75..79  = 0     (76..79 uninitialized in game; zeroed here)
//
// Linear index: X + workSide * Y  (global diamond coordinates)
// ============================================================================
struct WorkCell
{
    int data[20];  // 20 * 4 = 80 bytes

    WorkCell()
    {
        for (int i = 0; i < 20; ++i)
            data[i] = 0;
        data[16] = -1;
        Byte(74) = 1;
    }

    // Byte accessor for the flag bytes (e.g. +74 validity flag).
    unsigned char& Byte(int offset)
    {
        return reinterpret_cast<unsigned char*>(data)[offset];
    }
    unsigned char Byte(int offset) const
    {
        return reinterpret_cast<const unsigned char*>(data)[offset];
    }

    int& MapCoords() { return data[0]; }
    int  MapCoords() const { return data[0]; }
};

// ============================================================================
// CellIterator - exact replication of the game's diamond cell iterator
//
//   Reset       : sub_578350 (0x578350)
//   Next        : MapClass::CellIteratorNext (0x578290)
//
// State (from MouseClass/DisplayClass):
//   CellIterator_NextX / NextY : coordinates of the NEXT cell to return
//   CellIterator_CurrentY      : advance-branch calls remaining on diagonal
//   CellIterator_NextCell      : linear slot index into Cells.Items
//
// Iteration order: diagonals s = x+y in increasing order; within each
// diagonal, x increases / y decreases. The first cell returned is (1, W').
// Iteration terminates when the slot holds nullptr (outside the diamond).
// ============================================================================
class CellIterator
{
public:
    CellIterator() : slots_(nullptr), mapWidth_(0)
        , nextX_(0), nextY_(0), currentY_(0), slotIndex_(0) {}

    // Replicates sub_578350
    void Reset(MapCell* const* slots, int mapWidth)
    {
        slots_ = slots;
        mapWidth_ = mapWidth;
        nextX_ = 1;
        nextY_ = mapWidth;
        currentY_ = mapWidth - 1;
        slotIndex_ = 512 * mapWidth + 1;
    }

    // Replicates MapClass::CellIteratorNext; returns nullptr when done
    MapCell* Next()
    {
        int curY = currentY_;
        int oldSlot = slotIndex_;
        if (curY)
        {
            nextY_ -= 1;
            nextX_ += 1;
            currentY_ = curY - 1;
            slotIndex_ = oldSlot - 511;
        }
        else
        {
            int ny = nextY_;
            int nx = nextX_;
            nextX_ = ny;
            nextY_ = nx;
            if (((ny - mapWidth_ + nx - 1) & 1) != 0)
            {
                currentY_ = mapWidth_ - 1;
                nextY_ = nx + 1;
            }
            else
            {
                currentY_ = mapWidth_ - 2;
                nextX_ = ny + 1;
            }
            slotIndex_ = nextX_ + (nextY_ << 9);
        }
        return slots_[oldSlot];
    }

private:
    MapCell* const* slots_;
    int mapWidth_;
    int nextX_;
    int nextY_;
    int currentY_;
    int slotIndex_;
};

// ============================================================================
// MapGenConfig - generation parameters (from UI, key RandomMapGenerator fields)
// ============================================================================
struct MapGenConfig
{
    LandType   landType;     // this[15]
    int        theater;      // this[14]
    int        timeOfDay;    // this[18]  (0-3)
    int        sizeSlider;   // this[25] = this[26]  (0-3)
    int        playerCount;  // this[20]  (2-8)
    int        oreDensity;   // ore density index
    int        waterAmount;  // this[19]  water amount percent (0-100).
                            // Rolled by the UI layer per generation
                            // (sub_597260 @ 0x597282, per-LandType range
                            // tables 0x82B0A8 / 0x82B0BC), like the seed.
    uint32_t   randomSeed;   // this[29]  (dialog seed field)
};

// ============================================================================
// MapSizeResult - computed map dimensions
//
//   width/height   : visible size W x H (LocalSize = {2, 5, W, H})
//   mapWidth       : W' = W + 4   (MapRect.Width)
//   mapHeight      : H' = H + 12  (MapRect.Height)
//   workSide       : W' + H' + 1  (dword_89C2DC, sub_42AC00)
// ============================================================================
struct MapSizeResult
{
    int width;
    int height;
    int mapWidth;
    int mapHeight;
    int workSide;
};

// ============================================================================
// RMGSettings - all fields read from RMGMD.INI [General] (sub_5981F0)
// ============================================================================
struct RMGSettings
{
    int MinTiberium;   // RMGMinimumTiberium
    int MaxTiberium;   // RMGMaximumTiberium
    int MaxTrees;      // MaxTrees

    std::vector<int> LevelLightSettings;
    std::vector<int> TemperateAmbientLight;
    std::vector<int> SnowAmbientLight;
    std::vector<int> TemperateAmbientRed;
    std::vector<int> TemperateAmbientGreen;
    std::vector<int> TemperateAmbientBlue;
    std::vector<int> SnowAmbientRed;
    std::vector<int> SnowAmbientGreen;
    std::vector<int> SnowAmbientBlue;
    std::vector<int> VegetationMinimums;
    std::vector<int> VegetationMaximums;

    std::vector<std::string> TemperateOrePatchLamps;
    std::vector<std::string> SnowOrePatchLamps;

    void SetDefaults();
    int LevelLight(int timeOfDay) const;
    int AmbientLight(int theater, int timeOfDay) const;
    int VegetationMin(int landType) const;
    int VegetationMax(int landType) const;
};

// ============================================================================
// RandomMapGenerator - terrain generation body
//
// GenerateMapBody replicates the RNG-relevant core of sub_599650:
//   1. rng_.Seed(seed)          (sub_598960: qmemcpy(&dst_, Seed(this[29])))
//   2. ReInitMapData()          (sub_5981F0, no RNG consumption)
//   3. CalcMapSize()            (0x599665 - 0x59976a)
//   4. InitCells()              (CreateEmptyMap semantics, 512-stride slots)
//   5. InitWorkArray()          (0x59a2fa - 0x59a37f, 80 * workSide^2 bytes)
//   6. FillWorkCoords()         (0x59a385 - 0x59a3dc, iterator order)
//   7. random25Flag_            (0x59a4cc, exactly ONE Random() call)
//
// Verified via xrefs of dst_ (0xABE890): no other RNG consumer runs between
// the seeding in sub_598960 and sub_59A6C0 terrain generation.
// ============================================================================
class RandomMapGenerator
{
public:
    RandomMapGenerator();
    ~RandomMapGenerator();

    bool GenerateMapBody(const MapGenConfig& cfg);

    // Re-initialize map data from RMGMD.INI (replicates sub_5981F0)
    bool ReInitMapData();

    // Theater tile-family indices (IsometricTileTypeClass::ReadINI, 0x545150).
    // Reads the [General] keys ShorePieces / WaterSet / WaterfallEast /
    // WaterfallWest / WaterfallSouth / WaterfallNorth / CliffSet from
    // TEMPERATMD.INI (theater 0) or SNOWMD.INI (theater 1) next to the
    // executable into shorePieces_, waterTileIndex_, waterFamily4Base_ and
    // shoreTileIndex_. Missing keys or a missing file leave -1.
    void LoadTheaterTiles(int theater);

    // Regular terrain generation (replicates sub_59A6C0).
    // Segment 1 (0x59a724 - 0x59a738): flood every diamond cell with the
    // water base tile (game global nIdx = WaterSet).
    // Segment 2 (0x59a6f6 - 0x59a718): dispatch to the land type generator.
    // Segments 3-6 (isolated water fill, sub_57A0C0 smoothing, work array
    // reset, coast grass pass) are NOT implemented.
    void GenerateTerrain();

    // ---- Segment 2 land type generators (BODIES PENDING) ----
    // Common skeleton shared by all three (see sub_59BBC0_注释.md):
    //   genCode_ = 1;                 // this[194] = 1
    //   ClearWorkOccupancy();         // work data[15] = 0, whole map
    //   target = <per generator formula>;
    //   loop {
    //       seed = <per generator rule>;
    //       grown = GrowPatch(area, bounds, seed, 1, center, step, mode);
    //       if (grown) { ++genCode_; accumulated += grown; }
    //       pick next seed;
    //   } until target reached / attempt cap;
    void GenerateArchipelago();    // sub_59AD10: sub_59A8F0 block grid, step 0.25, mode 0
    void GenerateContinent();      // sub_59AFA0: single ellipse,          step 0.75, mode 1
    void GenerateTeamContinent();  // sub_59B200: two halves,              step 0.75, mode 1

    // Common generator prologue: iterate all cells in diamond order and
    // clear the work occupancy mark (data[15], byte 60). Verbatim prologue
    // of sub_59AD10 (0x59ad5e) / sub_59AFA0 (0x59b043) / sub_59B200 (0x59b063).
    void ClearWorkOccupancy();

    // Organic patch growth engine (sub_59BBC0) - BODY PENDING, full
    // annotated walkthrough in sub_59BBC0_注释.md.
    //   area         target cell count (forced >= 400 internally)
    //   bounds       boundary rect; nullptr = sentinel (unlimited)
    //   seedXY       packed seed (low16 X, high16 Y); (0,0) = random pick
    //   boundsMode   sub_59BAB0 a5: 0 = AABB, 1 = ellipse
    //   centerXY     packed region center for directional priority
    //   step         gaussian walk step a7 (0.25 archipelago / 0.75 continent)
    //   priorityMode a8: 0 = radial distance + noise, 1 = directional (sub_59B940)
    // Returns cells grown (seed + main loop + leftover queue sweep), 0 on
    // failure (map rolled back, caller retries with another seed).
    int GrowPatch(int area, const MapRectTag* bounds, int seedXY,
                  int boundsMode, int centerXY, double step, int priorityMode);

    // Special terrain generation (replicates sub_59C580).
    // Vanilla dispatch (sub_598960 @ 0x598aed - 0x598b0d):
    //   if (this[15] == 3 || this[15] == 4) {   // Inland / Mountainous
    //       if (this[19])                       // water amount nonzero
    //           sub_59C580(this);
    //   }
    //   else
    //       sub_59A6C0(this);                   // -> GenerateTerrain()
    // Unlike sub_59A6C0 (flood all water, then grow land), the LandType 3/4
    // base map stays all-land (cell reset leaves IsoTileTypeIndex = 0), so
    // this generator carves the special features (water / lake patches) -
    // the inverse role. Full annotated walkthrough: sub_59C580_注释.md.
    // Implemented: prologue (preparation, ++genCode_) + river stage dispatch
    //              (up to 10 GenerateRiver tries, first success stops) +
    //              river start / angle / width / length initialization
    //              (sub_59D510 head, 0x59d541 - 0x59d925) + the lake stage
    //              (10 tries, first success bumps the generation code).
    void GenerateSpecialTerrain();

    // One river attempt (replicates sub_59D510). Implemented: start /
    // angle / width / length initialization (0x59d541 - 0x59d925) + the
    // main-loop skeleton - (1) center diamond check, (2) cross-section
    // carving (generation-code stamping, pollution on old-water contact),
    // (3) river-mouth delta trigger (six gates + GenerateDelta dispatch),
    // (4) center advance (cx += cos, cy -= sin), (5) tributary fork (1%
    // roll each step, gaussian angle window, recursive call whose return
    // value overwrites the alive flag), (6) angle jitter (steps > 5;
    // gaussian sigma pi/10, rejection-clamped into theta0 +/- pi/2),
    // (7) width jitter (gaussian sigma 0.5, clamped into the fixed
    // [w0 - w0/2, w0 + w0/2] window; only when w0 >= 2), (8) the 0.5%
    // natural-termination roll. Post-loop: exit gates + terminal lake
    // (5.5) and top-level post-processing (5.6: smoothing, lakeshore
    // ring expansion, shore tile correction) implemented, plus the canyon
    // branch, the finish expansion and the rollback (5.7-5.9) with both of
    // the canyon's primitives (FindCandidateCenter, ExpandWaterBody) landed -
    // the whole chain now consumes RNG as vanilla does.
    // Full annotated walkthrough: sub_59C580_注释.md §5.2 - §5.9.
    //   startXY      packed start coords (low16 X, high16 Y);
    //                (0,0) = automatic mode (random edge start), used by
    //                the top-level call; nonzero = specified start
    //                (tributary recursion from the river main loop)
    //   initialAngle initial flow direction theta0 in radians; only used
    //                by the specified-start branch (vanilla number_16)
    //   isTributary  false = top-level call; true = tributary recursion
    //                (vanilla a4: 0 = top, nonzero = tributary; tributaries
    //                get no delta, no canyon lift and no post-processing.
    //                A river that forks a tributary sets this flag on
    //                itself - asm 0x59dea5 - and is demoted the same way
    //                for the rest of its lifetime.)
    // Returns true on success (step count already added to the water-cell
    // budget), false on failure (map already rolled back to all-land).
    bool GenerateRiver(int* startXY, double initialAngle, bool isTributary);

    // One river-mouth delta fan (replicates sub_59E740) - IMPLEMENTED.
    // Called by the river main loop's delta trigger (0x59ddf5) after all
    // six gates pass; carves a fan of water downstream of the river end
    // and, on success, advances the river mouth center 12 cells along the
    // fan heading so the main channel continues past the fan.
    //   genCode     generation code stamped on the fan cells
    //   startXY     packed first cell of the terminal cross-section
    //   endXY       packed last cell of the terminal cross-section
    //   direction   fan heading: 0 = -y, 2 = +x, 4 = +y, 6 = -x
    //   success     receives the result (vanilla v74[0])
    //   centerX/Y   river mouth center (in/out, advanced on success)
    void GenerateDelta(int genCode, int startXY, int endXY, int direction,
                       bool* success, double* centerX, double* centerY);

    // One lake attempt (replicates sub_59C920) - IMPLEMENTED.
    // Called from the river exit phase (0x59e22c) when the river ends by
    // natural termination, seeded with the river-mouth cell; the top-level
    // lake stage (GenerateSpecialTerrain stage 2) uses the same routine
    // with its own random start points.
    // Budget gate, node block + min-heap, qualification sweep, auto-mode seed
    // sampling, gaussian area sampling, priority growth loop, heap drain, size
    // gates, smoothing / lakeshore expansion / shore-tile fix and the failure
    // rollback. Its two subordinates are landed as well:
    // ClearPreviousGeneration (sub_5A0410) and the heap sift-down (sub_5AD870).
    //   startXY     packed seed cell (low16 X, high16 Y); (0,0) = automatic
    // Returns true on success; at the river exit a failure clears the
    // river's success flag (0x59e235).
    bool GenerateLake(int* startXY);

    // Four full-map smoothing passes over one water body (replicates
    // sub_57A0C0). Repairs the cells stamped with genCode; all call sites
    // pass flag = 0. Returns false to fail the caller.
    // Implemented: body (work-array reset + four iterator passes sharing one
    // success flag), pass 1 (FloodFill), pass 2 (CleanupTile) and passes 3/4
    // (SelectShoreTile - decision logic plus placement tail, including the
    // sub_57B440 stamp for the families whose geometry is tabulated).
    bool SmoothWaterBody(int genCode, int flag);

    // Ring expansion / absorption of one water body (replicates
    // sub_5A0160, full body recovered). Grows the body carrying `genCode`
    // outward one ring per mode step: mode 1 = lakeshore, 2 = riverside,
    // 6 = large-scale absorption; centerX/Y + rangeX/Y delimit the working
    // rect (full map = 0, 0, 512, 512); flag != 0 also accepts cells of the
    // previous generation (genCode - 1) and stamps `level` on placeholder
    // cells. Returns false when the ring meets another generation's water.
    bool ExpandWaterBody(int genCode, int mode, int centerX, int centerY,
                         int rangeX, int rangeY, int flag, int level);

    // sub_5A0700 - ring 0 of the body carrying `genCode`: its boundary cells
    // (every body cell that has an in-diamond neighbour outside the body),
    // appended once per outside neighbour exactly as vanilla does.
    std::vector<CellStruct> BuildWaterRing(int genCode) const;

    // sub_4865D0 - true when the cell's tile belongs to the water / shore
    // families: [shorePieces_, +42), [waterTileIndex_, +14) and four 4-wide
    // families (the game globals nIdx_0 @0xAA073C, nIdx_1 @0xABB110,
    // nIdx_2 @0xAA1050, nIdx_3 @0xAA10A0 - all INI-filled locally).
    bool IsWaterFamilyTile(const MapCell* cell) const;

    // Candidate-center search (sub_5A08D0). Picks a candidate center by
    // probability density; returns false when none qualifies.
    //   canyon lift (0x59e3a6): density 0.01, flag 1, rect {0,0,512,512},
    //                           anchor = the river's start cell - outputs
    //                           discarded
    //   delta fan   (0x59ec6a): density 0.003, flag 0 - outputs are the fan
    //                           center (doc §7 X_11 / v123)
    // The routine also mutates the work array: it stamps the generation code
    // on every absorbed cell (data[14]), sets the ring marker (byte 75) and
    // the visited marker (byte 15), and - when flag != 0 - walks the leftover
    // heap setting byte 56.
    bool FindCandidateCenter(int genCode, double density, const int* rect,
                             const CellStruct& anchor, int flag);

    // River rollback (sub_59D510 LABEL_151, 0x59e538 - 0x59e629): restore the
    // cells carrying `genCode` - and, when the river had placed a delta, those
    // carrying `genCode - 1` - to plain land at baseLevel_. Always returns
    // false so call sites read `return RollbackRiver(...)`.
    bool RollbackRiver(int genCode, int deltaCount);

    const MapSizeResult& GetSize() const { return size_; }

    const RMGSettings& GetSettings() const { return settings_; }
    bool GetIniLoaded() const { return iniLoaded_; }

    // Cell slot array (512-stride). Diamond cells point into the pool,
    // everything else is nullptr (InvalidCell sentinel).
    MapCell* const* GetCellSlots() const { return cellSlots_; }
    int GetSlotRows() const { return slotRows_; }
    int GetCellCount() const { return cellCount_; }

    const WorkCell* GetWorkCells() const { return workCells_; }
    int GetWorkCellCount() const { return size_.workSide * size_.workSide; }

    bool GetRandom25Flag() const { return random25Flag_; }

    int GetWaterAmount() const { return waterAmount_; }

    R250Random& RNG() { return rng_; }

    // Diamond existence test (MapClass::CreateEmptyMap):
    //   W' < x+y <= W'+2H'  and  |x-y| < W'
    bool CellExists(int x, int y) const
    {
        int s = x + y;
        if (s <= size_.mapWidth || s > size_.mapWidth + 2 * size_.mapHeight)
            return false;
        int d = x - y;
        if (d < 0) d = -d;
        return d < size_.mapWidth;
    }

private:
    MapSizeResult CalcMapSize(const MapGenConfig& cfg) const;
    void InitCells();
    void InitWorkArray();
    void FillWorkCoords();

    // ---- SmoothWaterBody (sub_57A0C0) support ----
    // Work array accessor by linear index (sub_58C2C0): base + 80 * index.
    WorkCell& WorkAtLinear(int index) { return workCells_[index]; }

    // Work array accessor by diamond coords (sub_58C2A0): base + 80*x + 80*W'*y.
    WorkCell& WorkAt(int x, int y) { return workCells_[x + size_.workSide * y]; }

    // ---- GenerateLake (sub_59C920) support ----
    // Ring-spread relabel (sub_5A0410). Called once by the lake auto-seed pass
    // as ClearPreviousGeneration(0, 2, -2) (0x59ca9a): grows `rings` rings
    // outward from the body carrying `genCode`, stamping each visited cell's
    // generation mark with `mark` and clearing its tile.
    void ClearPreviousGeneration(int genCode, int rings, int mark);

    // ---- FloodFill (sub_57A430) support ----
    // Tile predicates: sub_485060 (water tile, IsoTileTypeIndex in
    // [nIdx, nIdx+14)) and sub_486380 (placeholder tile, 0 or 0xFFFF).
    bool IsWaterTile(const MapCell* cell) const;
    bool IsPlaceholderTile(const MapCell* cell) const;

    // Cell accessor mirroring MapClass::GetCellAt_MapCrd: the cell at (x, y),
    // or invalidCell_ (MapCoords stamped, tile 0) when the slot is null or out
    // of range.
    MapCell* CellAt(int x, int y);

    // Raw slot accessor (Cells.Items[index]) - no InvalidCell fallback;
    // nullptr when the index is out of range or the slot is null.
    MapCell* RawSlot(int index);

    // 8-neighbour lookup (CellClass::GetNeighbourCell over the Neighbours
    // table): the cell one step from `cell` in direction `facing` (0 = N,
    // 1 = NE, ... 7 = NW), with the InvalidCell fallback.
    MapCell* GetNeighbourCell(const MapCell* cell, int facing);

    // TileNeighbourMask (sub_57B210): 8-direction connectivity mask of the
    // cell's water neighbours. mode 0 = require placeholder tile, mode 1 =
    // reject water tile, mode 2 = no tile gate. All modes return the same mask
    // when they do not early-return; a mask already cached in the work cell's
    // data[16] is returned as-is.
    int TileNeighbourMask(MapCell* cell, int mode);

    // Foundation-preview reset (sub_4A8BF0). Runs as the first statement of
    // SmoothWaterBody; clears the DisplayClass foundation state carried in
    // foundationPreview_ (see FoundationPreviewState).
    void ResetPreviewState();

    // Foundation cell stamping (sub_4A95A0, YRpp DisplayClass::MarkFoundation):
    // sets or clears AltCellFlags_ContainsBuilding on every cell of the
    // foundation list foundationPreview_.Data, each taken relative to baseCell.
    void MarkFoundation(CellStruct baseCell, bool mark);

    // The three smoothing passes driven by SmoothWaterBody:
    //   pass 1  FloodFill       (sub_57A430) - IMPLEMENTED; recursive flood
    //                                        fill, returns false on foreign-
    //                                        water pollution
    //   pass 2  CleanupTile     (sub_57A320) - IMPLEMENTED; placeholder tile
    //                                        reclaim (return ignored by caller)
    //   pass 3/4 SelectShoreTile(sub_57ACF0) - IMPLEMENTED (RNG draw, mask
    //                                        gate, n12 branch selection,
    //                                        mode-1 edge scans, plus the
    //                                        placement tail incl. the
    //                                        PlaceIsoTile stamp); consumes
    //                                        one RNG draw per cell.
    bool FloodFill(MapCell* cell, int genCode, int flag);
    int  CleanupTile(MapCell* cell, int genCode);
    bool SelectShoreTile(MapCell* cell, int mode, int genCode, int flag);

    // Foundation-preview center move (sub_4A91B0). Sets
    // foundationPreview_.CenterCell to `target` and returns the previous
    // center - the tail of SelectShoreTile uses it to point the isotile
    // foundation at the shore anchor cell. Vanilla has two branches; only
    // the CurrentFoundation_Data == null one is reachable here
    // (ResetPreviewState clears Data and nothing in the generation path ever
    // sets it again), which is exactly the swap below. The Data != null
    // branch (unmark the old footprint, mark the new one, recompute
    // InAdjacent / NoShrouded) and the "target == (0,0) -> read the mouse"
    // special case both need the live DisplayClass and never run.
    CellStruct SetFoundationCenter(CellStruct target);

    // Isotile foundation stamping (sub_57B440) - IMPLEMENTED, shared with the
    // cliff placement chain. Stamps the isotile currently selected in
    // currentBuildingType_ onto every cell of its foundation footprint,
    // anchored at foundationPreview_.CenterCell, subject to the vanilla
    // acceptance / occupancy rules.
    //   lo, hi    accepted existing-tile range (mode 1: 0..0, mode 2:
    //             shorePieces_..shorePieces_+41)
    //   level     the source cell's Level (vanilla reads a signed byte)
    //   genCode   generation code (forced to 0 when flag != 0)
    //   placed    out flag: cleared when the stamp is rejected
    //   flag      nonzero selects the "no generation code" variant
    // The caller (SelectShoreTile) ignores the return value and only reads
    // *placed, exactly as vanilla does.
    // Geometry source: the footprint is resolution-time data (the isotile type
    // object's ArrayIndex +0x294, foundation width +0x2E4 / height +0x2E8 and
    // the per-cell pointer array inside its SHP image at GetImage() + 0x10 -
    // all built by IsometricTileTypeClass::ReadINI from the theater's tile INI
    // and ART). The 42 shore footprints are therefore measured once from the
    // shipped tile art and tabulated in MapGen.cpp (see kShoreFootprints).
    bool PlaceIsoTile(int lo, int hi, int level, int genCode,
                      bool* placed, int flag);

    MapGenConfig config_;
    MapSizeResult size_;
    RMGSettings  settings_;
    bool         iniLoaded_;
    R250Random   rng_;

    MapCell*  cellPool_;    // allocated CellClass objects (diamond cells)
    MapCell** cellSlots_;   // 512-stride pointer array with nullptr sentinel
    int       slotRows_;    // slot array height (W' + H' + 1)
    int       cellCount_;   // number of diamond cells

    WorkCell* workCells_;

    // MapClass::InvalidCell sentinel: returned by CellAt when the requested
    // slot is null / out of range. Only MapCoords is meaningful (stamped with
    // the requested coords); the tile fields stay at their constructed values.
    MapCell   invalidCell_;

    // DisplayClass foundation-preview state (see FoundationPreviewState).
    FoundationPreviewState foundationPreview_;

    bool random25Flag_;    // RMG this[196] (byte 0x310): "deltas allowed"
                           // switch, rolled once with the main RNG at the
                           // end of the land pass (sub_599650 0x59a4cc:
                           // Random_w() < 0.25). Gates the river-mouth
                           // delta trigger (sub_59D510 0x59dcfc).
    int  baseLevel_;        // RMG this[195] = 4
    int  usedWaterCells_;   // RMG this[193]: water cells already spent against
                            // the river / lake budget. Grown by the river step
                            // count on success (sub_59D510 0x59e525) and read
                            // by the lake budget (sub_59C920 0x59c970, doc
                            // §6.1). Reset per map alongside baseLevel_.
    int  genCode_;          // RMG this[194]: generation code, ++ per successful
                            // patch; generators enter with 1; reset to 0 at the
                            // end of sub_598960 (0x5993b5)
    int  waterAmount_;      // RMG this[19]: water amount percent (0-100).
                            // Set from MapGenConfig::waterAmount, which the
                            // UI layer rolls per generation (sub_597260 @
                            // 0x597282: RandomRanged(0x82B0A8[landType],
                            // 0x82B0BC[landType]) with the UI randomizer
                            // this_pRandomizer - a different stream from
                            // dst_, so this roll never consumes generation
                            // RNG). A roll of 0 keeps LandType 3/4 all-land
                            // (sub_59C580 skipped, same as vanilla).
    // ---- theater tile-family indices (IsometricTileTypeClass::ReadINI) ----
    // All of these come from [General] keys of the theater INI; LoadTheaterTiles
    // turns each key (a TileSet SECTION NUMBER) into the running tile count at
    // that section - see its comment in MapGenRiver.cpp:
    //   waterTileIndex_          <- WaterSet           nIdx   @0xAA0738
    //   shoreTileIndex_          <- CliffSet           IsoTileTypeIndex_0 @0xAA0E18
    //   waterCliffsIndex_        <- WaterCliffs        (Cliff/Water pieces)
    //   destroyableCliffsIndex_  <- DestroyableCliffs
    //   shorePieces_             <- ShorePieces        nIdx_4 @0xABAD28
    //   waterFamily4Base_[0..3]  <- WaterfallEast / West / South / North
    int  waterTileIndex_;          // WaterSet: base tile of the water group
    int  shoreTileIndex_;          // CliffSet: base of the cliff family (40
                                   // wide) - also the tile stamped on the cells
                                   // still on 0/0xFFFF after the ring expansion
    int  waterCliffsIndex_;        // WaterCliffs: Cliff/Water pieces (28 wide)
    int  destroyableCliffsIndex_;  // DestroyableCliffs (2 wide)
    int  cliffRampsIndex_;         // CliffRamps (20 wide)
    int  waterCavesIndex_;         // WaterCaves (4 wide)
    int  bridgeSetIndex_;          // BridgeSet (16 wide)
    int  woodBridgeSetIndex_;      // WoodBridgeSet (16 wide)
    int  waterFamily4Base_[4];     // the four 4-wide waterfall families, in
                                   // sub_4865D0's test order (East, West, South,
                                   // North)

    // ---- theater shore-tile data (IsometricTileTypeClass::ReadINI) ----
    int        shorePieces_;          // game global dword_ABAD28: base index
                                      // of the shore tile group (the [General]
                                      // key "ShorePieces"); valid shore
                                      // variants are shorePieces_ + (0..41).
    CellStruct shoreAnchor_[42];      // game global table word_ABDB64: paired
                                      // int16 X/Y anchor offsets indexed by
                                      // the shore variant n12. All {0,0} in
                                      // the static image; filled at runtime.
    int        currentBuildingType_;  // MouseClass::Instance.CurrentBuildingType:
                                      // the isotile index currently selected
                                      // for placement - set by SelectShoreTile,
                                      // consumed by PlaceIsoTile.
};

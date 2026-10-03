// ============================================================================
// MapGenTech.cpp - the "RMG: Adding tech buildings" stage
// (sub_598960 @ 0x598EBF - 0x598EE4) and its body sub_5A95B0.
//
// The stage slice is a single gated call:
//
//     0x598EBF  push "RMG: Adding tech buildings\n", nullsub_1    debug print
//     0x598EC9  eax = this[0x3C]                 ; landType
//     0x598ECF  if (eax != 0)                    ; 0 = Archipelago: the only skip
//     0x598ED5      sub_5A95B0(this)
//     0x598EDA  if (psub_48D1D0) psub_48D1D0()   ; UI / session callback, not ported
//
// Full annotated walkthrough: 598EBF_AddingTechBuildings.c and 5A95B0.c in the
// decompile folder.
//
// sub_5A95B0 has two entirely different paths:
//
//   Branch A - landType == 2 (TeamContinent)
//       Draw a round count n in {0,1,2}:
//           n = F2I64(Random() * dbl_7ED8C0), dbl_7ED8C0 = 3 * kUnitScale,
//           reject while n > 2.
//       Then run the whole region list n times, handing every region whose
//       startingPoints (+0x20) is > 0 to sub_595400 (GiveRegionATechBuilding).
//
//   Branch B - any other land type (0/1/3/4, i.e. also the Inland / Mountainous
//              maps this project targets)
//       Draw a building count n in {0,1,2,3,4}:
//           n = F2I64(Random() * 5 * kUnitScale), reject while n > 4.
//       Then per building: draw a type from RulesClass::NeutralTechBuildings
//       (one draw, reject > count-1) and try up to 100 times to find a spot
//       anywhere on the map:
//           sample a work slot (one draw each) -> skip the slots outside the
//           diamond (packed coords (0,0)) -> the cell must carry no own tile ->
//           take its Level -> every foundation cell must pass the six-clause
//           test of FoundationFitsAt -> place. The sampling stops after 200
//           examined cells and then runs the fit test on the (0,0) cell, which
//           can never pass.
//
// Route B: the port has no live object system, so a successful placement is
// recorded through RecordPlacedBuilding (a MapStructure plus
// AltCellFlags_ContainsBuilding on every foundation cell). Two things have no
// counterpart: the owner lookup (HouseClass::FindByCountryIndex of "Neutral" -
// the record keeps the fixed name) and Unlimbo's world coordinates (the .map
// [Structures] section stores the cell, which MapStructure keeps).
//
// RNG: one draw for the count, one per building for its type, one per sampled
// work slot. Nothing else in this stage draws.
// ============================================================================

#include "pch.h"
#include "MapGen.h"

// ---------------------------------------------------------------------------
// sub_5A95B0 (0x5A95B0 - 0x5A9915)
// ---------------------------------------------------------------------------
void RandomMapGenerator::AddTechBuildings()
{
    if (workCells_ == nullptr)
        return;

    const int landType = static_cast<int>(config_.landType);   // 0x5a95b6

    // 0x598ecf: the stage slice is skipped entirely for LandType_Archipelago
    // (0). Every other land type - including the Inland (3) / Mountainous (4)
    // maps this project targets - reaches sub_5A95B0.
    if (landType == 0)
        return;

    // ---- Branch A: TeamContinent (0x5a95bf - 0x5a9626) --------------------
    if (landType == 2)
    {
        int rounds;
        do
        {
            rounds = F2I64(static_cast<double>(rng_.Next())
                           * (3.0 * kUnitScale));              // 0x5a95df
        }
        while (rounds > 2);                                    // 0x5a95e7

        for (int k = 0; k < rounds; ++k)                       // 0x5a9626
        {
            // The vanilla re-reads the region array and its count after every
            // call (0x5a9615 / 0x5a961b); sub_595400 never changes either, so a
            // straight pass over the vector is equivalent.
            for (size_t i = 0; i < regions_.size(); ++i)       // 0x5a9602
            {
                MapRegion* region = regions_[i];
                if (region != nullptr && region->startingPoints > 0) // +0x20
                    GiveRegionATechBuilding(region);           // 0x5a9610
            }
        }
        return;
    }

    // ---- Branch B: every other land type (0x5a9630 - 0x5a9908) ------------
    // The vanilla resolves the owner first:
    //     HouseClass::FindByCountryIndex(
    //         HouseTypeClass::FindIndexOfName("Neutral"))     // 0x5a9635 / 0x5a9641
    // It draws no RNG and the port records the fixed owner name in the
    // MapStructure, so there is nothing to resolve here.

    int count;
    do
    {
        count = F2I64(static_cast<double>(rng_.Next())
                      * (5.0 * kUnitScale));                   // 0x5a9665
    }
    while (count > 4);                                         // 0x5a966d

    // Deviation: with no type list there is nothing to draw. The vanilla would
    // index Items[0] of an empty list; the shipped rulesmd.ini always has the
    // list. The count draw above is kept so the RNG stays aligned.
    if (neutralTechBuildings_.empty())
    {
        DiagLog("TECH-DIAG enter landType=%d types=0 (list empty, returning)",
                landType);
        return;
    }

    // ---- [TECH-DIAG] temporary instrumentation: read-only, no behaviour ----
    DiagLog("TECH-DIAG enter landType=%d countDrawn=%d types=%d",
            landType, count, static_cast<int>(neutralTechBuildings_.size()));
    for (size_t ti = 0; ti < neutralTechBuildings_.size(); ++ti)
        DiagLog("TECH-DIAG type[%d]=%s %dx%d", static_cast<int>(ti),
                neutralTechBuildings_[ti].name,
                neutralTechBuildings_[ti].width,
                neutralTechBuildings_[ti].height);
    {
        int nPH = 0, nPHSlope = 0, nWater = 0, nOther = 0;
        for (int sy = 0; sy < size_.workSide; ++sy)
        {
            for (int sx = 0; sx < size_.workSide; ++sx)
            {
                const int packed =
                    workCells_[sx + size_.workSide * sy].MapCoords();
                if (packed == 0)
                    continue;
                const CellStruct cc{
                    static_cast<int16_t>(packed & 0xFFFF),
                    static_cast<int16_t>(static_cast<uint32_t>(packed) >> 16) };
                if (!IsWithinUsableArea(cc, true))
                    continue;
                const MapCell* c = CellAt(cc.X, cc.Y);
                const int t = c->IsoTileTypeIndex;
                if (t == 0 || t == 0xFFFF)
                {
                    if (c->SlopeIndex != 0) ++nPHSlope; else ++nPH;
                }
                else if (IsWaterTile(c)) ++nWater;
                else ++nOther;
            }
        }
        DiagLog("TECH-DIAG usable cells: phFlat=%d phSlope=%d water=%d other=%d",
                nPH, nPHSlope, nWater, nOther);

        for (size_t a = 0; a < neutralTechBuildings_.size(); ++a)
        {
            const NeutralTechBuilding& tt = neutralTechBuildings_[a];
            int fits = 0;
            for (int sy = 0; sy < size_.workSide; ++sy)
            {
                for (int sx = 0; sx < size_.workSide; ++sx)
                {
                    const int packed =
                        workCells_[sx + size_.workSide * sy].MapCoords();
                    if (packed == 0)
                        continue;
                    const CellStruct cc{
                        static_cast<int16_t>(packed & 0xFFFF),
                        static_cast<int16_t>(static_cast<uint32_t>(packed) >> 16) };
                    const MapCell* c = CellAt(cc.X, cc.Y);
                    if (!IsPlaceholderTile(c) || c->SlopeIndex != 0)
                        continue;
                    if (FoundationFitsAt(cc, c->Level, tt.width, tt.height))
                        ++fits;
                }
            }
            DiagLog("TECH-DIAG feasible anchors %s %dx%d = %d",
                    tt.name, tt.width, tt.height, fits);
        }
    }

    for (int k = 0; k < count; ++k)                            // 0x5a9908
    {
        // One draw for the building type (0x5a9690 - 0x5a96fd). In the vanilla
        // this is also where the BuildingClass is allocated and constructed.
        const int typeCount = static_cast<int>(neutralTechBuildings_.size());
        int typeIndex;
        do
        {
            typeIndex = F2I64(static_cast<double>(rng_.Next())
                              * static_cast<double>(typeCount) * kUnitScale);
        }
        while (typeIndex > typeCount - 1);                     // 0x5a96df

        const NeutralTechBuilding& type =
            neutralTechBuildings_[static_cast<size_t>(typeIndex)];

        bool placed = false;                                   // v22
        // [TECH-DIAG] failure bookkeeping - 1 object, 2 not-placeholder,
        // 3 level, 4 rock, 5 usable area, 6 work byte +69.
        int gaveUp = 0;
        int rWhy[7] = { 0, 0, 0, 0, 0, 0, 0 };
        int attemptsUsed = 0;
        // [port-only] 两道：先要求 1 格平坦围裙（避开刻区域时已经雕好的悬崖
        // 斜坡——实测 rmg_20261003_125504 的建筑虽地基平整，却紧贴 510/513
        // 坡带）；100 次仍找不到再用原版只看地基的规则，保证不少放。
        for (int apronPass = 0; apronPass < 2 && !placed; ++apronPass)
        {
            const int apron = (apronPass == 0) ? 1 : 0;
        for (int attempt = 0; attempt < 100 && !placed; ++attempt) // 0x5a9718
        {
            ++attemptsUsed;
            // Sampling (0x5a9726 - 0x5a9786). `examined` is the vanilla's n200:
            // a per-attempt counter of the cells looked at. It is capped at 200,
            // and on overflow the vanilla gives up with coords (0,0) and still
            // runs the fit test - which fails, the (0,0) cell being outside the
            // diamond.
            const int slotCount = size_.workSide * size_.workSide;
            CellStruct coords{ 0, 0 };
            int examined = 0;                                  // n200
            bool timedOut = false;                            // [TECH-DIAG]
            for (;;)
            {
                const int slot = rng_.RandomFloatRange(0, slotCount - 1); // 0x5a973a
                const int packed = workCells_[slot].MapCoords();          // 0x5a976f
                if (packed == 0)                               // (0,0) slot: no cell
                    continue;                                  // 0x5a9750
                ++examined;                                    // 0x5a9765
                coords = CellStruct{
                    static_cast<int16_t>(packed & 0xFFFF),
                    static_cast<int16_t>((uint32_t)packed >> 16) };
                if (examined > 200)                            // 0x5a9773
                {
                    coords = CellStruct{ 0, 0 };               // 0x5a979e
                    timedOut = true;                          // [TECH-DIAG]
                    break;
                }
                if (IsPlaceholderTile(CellAt(coords.X, coords.Y))) // 0x5a9786
                    break;
            }
            if (timedOut)
                ++gaveUp;

            // Fit test (0x5a97c1 - 0x5a987e): the same six clauses sub_595400
            // uses, over the type's W x H foundation at the sampled cell.
            // [port-only] 第一道再加一圈平坦围裙；第二道退回原版口径。
            const int level = CellAt(coords.X, coords.Y)->Level; // 0x5a97c1
            if (FoundationFitsAtFlat(coords, level,
                                     type.width, type.height, apron))
            {
                // Vanilla Unlimbos here and answers 1 (0x5a98c2 / 0x5a98cc).
                if (apron == 0)
                    DiagLog("TECH-DIAG building fell back to foundation-only rule: %s",
                            type.name);
                RecordPlacedBuilding(coords, type.name,
                                     type.width, type.height);
                placed = true;
                rWhy[0]++;                                    // [TECH-DIAG]
            }
            else
            {
                // [TECH-DIAG] classify why the foundation was rejected.
                int why = 0;
                for (int row = 0; row < type.height && why == 0; ++row)
                {
                    for (int col = 0; col < type.width; ++col)
                    {
                        const int16_t fx =
                            static_cast<int16_t>(coords.X + col);
                        const int16_t fy =
                            static_cast<int16_t>(coords.Y + row);
                        const MapCell* fc = CellAt(fx, fy);
                        if ((fc->AltFlags & AltCellFlags_ContainsBuilding) != 0)
                        { why = 1; break; }
                        if (!IsPlaceholderTile(fc))            { why = 2; break; }
                        if (fc->Level != level)                { why = 3; break; }
                        if (fc->LandType == 3)                 { why = 4; break; }
                        if (!IsWithinUsableArea(CellStruct{ fx, fy }, true))
                                                               { why = 5; break; }
                        if (workCells_[fx + size_.workSide * fy].Byte(69) != 0)
                                                               { why = 6; break; }
                    }
                }
                ++rWhy[why];
            }
        }
        }

        DiagLog("TECH-DIAG building k=%d idx=%d %s %dx%d placed=%d attempts=%d "
                "gaveUp=%d why[ok=%d obj=%d tile=%d lvl=%d rock=%d area=%d mark=%d]",
                k, typeIndex, type.name, type.width, type.height,
                placed ? 1 : 0, attemptsUsed, gaveUp,
                rWhy[0], rWhy[1], rWhy[2], rWhy[3], rWhy[4], rWhy[5], rWhy[6]);

        // A failed run leaves nothing behind: the vanilla deletes the
        // BuildingClass (0x5a98fc), the port never created one. The type was
        // drawn before the attempts either way.
    }

    DiagLog("TECH-DIAG branchB done, structures on ledger=%d",
            static_cast<int>(structures_.size()));
}

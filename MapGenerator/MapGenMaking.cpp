// ============================================================================
// MapGenMaking.cpp - the "Making regions" stage of the random map generator
//
//   MakeRegions             sub_598960 @ 0x598D44   stage body - the only
//                                                   function in this file
//
// The stage's six calls are the subordinate functions, and every one of them
// lives in MapGenMakingSub.cpp, one function per vanilla routine:
//
//   [MapGenMakingSub.cpp]
//   RebuildRegionBodies     sub_58EBC0   rebuild every region body + settle/merge
//   SplitOrDropRegion       sub_58D620   split / drop one large region
//   RegionNodePriority      sub_58C6F0   the growth node priority key
//   ReseedRegions           sub_58EF10   destroy + re-seed, adjacency, ramps
//   CliffPass               sub_579010   one recursive cliff-blob step
//   LinkRegionNeighbours    sub_58F0C0   a region's neighbour-id vector
//   CarveRegionRamps        sub_5905D0   ramps between neighbouring regions
//   FixCliffLevels          sub_5A19E0   cliff edge / corner +-4 Level fix-up
//   PlaceCliffs             sub_578E60   cliff placement driver
//   CorrectCliffTiles       sub_5A17F0   cliff correction pass
//   FillGreenPlaceholders   sub_59B740   fill the leftovers next to green ground
//
// The stage sits between "RMG: Init regions" (0x598C24, MapGenRegion.cpp) and
// "RMG: Recalculating cell attributes" (0x598E1F): its debug string is at
// 0x82BEEC and referenced only from 0x598D44. Five of the six calls are gated on
// LandType 3 / 4 (Inland / Mountainous) - the line this project targets; the
// last one runs for every land type.
//
// Vanilla body (disasm slice 0x598D44 - 0x598E1E; annotated copy with the raw
// listing: 598D44_MakingRegions.c in the project's decompile folder):
//   0x598D55  landType = this[0x3C]
//   0x598D58  if (landType == 4 || landType == 3)
//   {
//   0x598D62      sub_58EBC0()
//   0x598D67      sub_58EF10()
//   0x598D6E      sub_5A19E0(this)
//   0x598D7B      sub_578E60(0, -1)
//   0x598D82      sub_5A17F0(this)
//   }
//   0x598D87  ... UI / session / psub_48D1D0 tail - NOT ported (see below)
//   0x598E1A  sub_59B740(this)
//
// Deliberately not ported: the 0x598D87 - 0x598E18 tail - the progress-bar
// reset / session notification (sub_643C50 / sub_69AE90), the WM_PAINT repaint
// (sub_641140 / SendMessageA / sub_5E7EB0) and the psub_48D1D0 hook callback.
// This tool only generates maps and has no multiplayer, and the tail touches
// neither the work array, the region array, the cells nor the RNG (checked
// against the full dst_ @0xABE890 xref inventory).
//
// The subordinates are declared and called in the vanilla order. They used to
// live below this point; they now sit in MapGenMakingSub.cpp, which also carries
// each one's ported / still-stub status and the decompile pointer. The
// decompiles themselves are in the project's decompile folder (58EBC0.c,
// 58EF10.c, 5A19E0.c, 578E60.c, 5A17F0.c, 59B740.c plus the second-level files
// listed in 598D44_MakingRegions.c).
// ============================================================================

#include "pch.h"
#include "MapGen.h"

// ---------------------------------------------------------------------------
// MakeRegions - the "RMG: Making regions" stage of sub_598960, 0x598D44 ..
// 0x598E1E.
//
// The gate is the only land-type dependency: LandType 3 (Inland) / 4
// (Mountainous) run the whole cliff / region-merge / ramp chain, every other
// land type jumps straight to the placeholder fill. The vanilla UI / session
// tail between the gate and the last call is not ported - see the file header.
// ---------------------------------------------------------------------------
void RandomMapGenerator::MakeRegions()
{
    // ---- 0x598d55 - 0x598d60: the LandType 3/4 gate ----------------------
    const int landType = static_cast<int>(config_.landType);

    if (landType == 3 || landType == 4)
    {
        RebuildRegionBodies();                      // 0x598d62  sub_58EBC0
        // [SNAPSHOT-OFF] SaveStageSnapshot("RebuildRegionBodies");
        ReseedRegions();                            // 0x598d67  sub_58EF10
        // [SNAPSHOT-OFF] SaveStageSnapshot("ReseedRegions");
        FixCliffLevels();                           // 0x598d6e  sub_5A19E0
        // [SNAPSHOT-OFF] SaveStageSnapshot("FixCliffLevels");
        PlaceCliffs();                              // 0x598d7b  sub_578E60
        // [SNAPSHOT-OFF] SaveStageSnapshot("PlaceCliffs");
        CorrectCliffTiles();                        // 0x598d82  sub_5A17F0
        // [SNAPSHOT-OFF] SaveStageSnapshot("CorrectCliffTiles");
        RepairCliffPieces();                        // port-only swallowed-piece repair
        // [SNAPSHOT-OFF] SaveStageSnapshot("RepairCliffPieces");
    }

    // ---- 0x598e1a: runs for every land type ------------------------------
    FillGreenPlaceholders();                        // sub_59B740
    // [SNAPSHOT-OFF] SaveStageSnapshot("FillGreenPlaceholders");
}

// ============================================================================
// MapGenCleanup.cpp - the "RMG: Cleanup" stage
// (sub_598960 @ 0x5993A5 - 0x59944C).
//
// The stage is a pure teardown: it touches no cell, no tile and no RNG. It
// releases the scratch the generation chain allocated, so the generator
// instance can be handed the next map:
//
//   0x5993AF / 0x5993B5  this[193] = this[194] = 0
//                        two instance fields at +0x304 / +0x308. The port does
//                        not model them (nothing reads them either), so there
//                        is nothing to zero.
//   0x5993BB - 0x5993D0  operator delete(dword_ABED10); dword_ABED10 = 0
//                        The 80-byte-per-cell work array.
//   0x5993D6 - 0x59943C  the region list (dword_ABDF94, count dword_ABDFA0),
//                        walked BACKWARDS from count - 1 down to 0. Per region:
//                          call [eax] (with 1)   the virtual deleting dtor
//                          removal from dword_ABDF90 (virtual, then
//                          sub_5AD790 to hand the slot back)
//                          [region+0x28] = VectorClass<Cell>::vftable
//                          sub_42F7C0(region+0x28)  that embedded vector's dtor
//                          operator delete(region)
//   0x599446             dword_ABED14 = 0
//                        the region-id counter (the tiberium stage's tail
//                        zeroes the same global; the vanilla does both).
//   0x59944C             sub_568BB0(1), MouseClass's per-cell attribute array
//                        teardown - the two parallel arrays the earlier stages
//                        index through (the port's levelAndPassability_ and
//                        friends).
//
// Full annotated slice: 5993A5_Cleanup.c.
//
// The port's ReleaseRegionObject(region, true) is exactly the vanilla's
// "remove from the list + dtor + operator delete" sequence (it erases the
// pointer from regions_ and deletes the object), so the region loop reuses it.
//
// NOTE: every container released here is re-created at the head of the next
// Generate call (InitCells / InitWorkArray / the stage inits), so this stage is
// behaviourally a no-op for the port. It is implemented anyway: the release is
// then explicit, and the stage list stays complete.
// ============================================================================

#include "pch.h"
#include "MapGen.h"

void RandomMapGenerator::Cleanup()
{
    // ---- 0x5993BB - 0x5993D0: the work array ------------------------------
    delete[] workCells_;
    workCells_ = nullptr;

    // ---- 0x5993D6 - 0x59943C: every region object -------------------------
    // The vanilla walks a fixed index range backwards over the list; the port's
    // helper erases the pointer as it goes, so pop from the back instead - each
    // region is then still visited exactly once.
    while (!regions_.empty())
        ReleaseRegionObject(regions_.back(), true);

    // ---- 0x599446: the region-id counter ----------------------------------
    regionIdCounter_ = 0;

    // ---- 0x59944C: MouseClass's per-cell attribute arrays -----------------
    // Four parallel containers in the port. The vanilla frees the buffers, so
    // release the capacity too rather than only clearing.
    std::vector<CellLevelPassability>().swap(levelAndPassability_);
    std::vector<int>().swap(levelAndPassability2_);
    std::vector<uint8_t>().swap(passabilityCopy_);
    for (int i = 0; i < 256; ++i)
    {
        zoneConnections_[i].clear();
        zoneConnections_[i].shrink_to_fit();
    }

    // ---- the elevation grid ----------------------------------------------
    // Already released by FinalizeElevationSlopes (sub_6B3850's tail clears
    // dword_B0B6EC); this only drops the port's own storage.
    elevGrid_.clear();
    elevGrid_.shrink_to_fit();
}

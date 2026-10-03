// ============================================================================
// MapGenDone.cpp - the "RMG: Done" stage, the last stage of the main flow
// (sub_598960 @ 0x59947E - 0x59951A), plus the port's progress ladder.
//
// The stage is progress / dialog bookkeeping, not map data. In order:
//
//   0x59947E  the 100 % tick - if LOBYTE(ScenarioClass::Instance->unknown_3598)
//             is set, sub_69AE90(199) pumps the network session; otherwise
//             sub_643C50(&progress, 0, 100.0, NAN) drives the local progress bar
//   0x5994B0  the "RMG: Done\n" debug print
//   0x5994BA  v35 == LOBYTE(unknown_3598) == 0 (captured at 0x5989E7): on the
//             local path only, hide dialog control 1592 (GetDlgItem + ShowWindow
//             SW_HIDE), reset the bar (sub_643C50(0, 0.0)), and detach it
//             (sub_643E70 -> progress->hWnd = 0)
//   0x59951F  epilogue: the function returns
//
// `unknown_3598` (ScenarioClass +0x3598, YRpp's name; only the low byte is read)
// picks between the two ways of reporting progress: != 0 pumps the multiplayer
// session (sub_69AE90 - IPXManagerClass, NodeNameType player names, Sleep(20)),
// == 0 writes the on-dialog progress bar object at dword_AC4F58 directly. The
// same flag opens the function (0x5989DC arms the local bar) and gates
// sub_599650 five more times.
//
// Full annotated slice, the tick ladder and the decompiles of sub_69AE90 /
// sub_643C50 / sub_643E70 / sub_642A60 / sub_643E90: 5994B0_Done.c.
//
// THE PORT
// ----------------------------------------------------------------------------
// The port has no dialog and no progress-bar object, but it does have a UI, so
// the stage is implemented as the local (single-player) path it describes:
//
//   - ReportProgress(100) is the 100 % tick (sub_643C50(0, 100.0));
//   - the "RMG: Done" banner has no port counterpart (the result dialog reports
//     the finished run), and hiding dialog control 1592 is unnecessary because
//     the port's preview panel is always visible;
//   - the teardown is modelled faithfully: the slot-0 percentage goes back to 0
//     (sub_643C50(0, 0.0)) and the sink is detached (sub_643E70's
//     progress->hWnd = 0).
//
// The percentages the UI shows come from the main flow: ReportProgress(55..95)
// is called between the stages in WinMain.cpp, at the points where the vanilla
// emits its sub_643C50 ticks - it is the same flow, so the ladder matches the
// table in 5994B0_Done.c one for one.
// ============================================================================

#include "pch.h"
#include "MapGen.h"

void RandomMapGenerator::SetProgressSink(ProgressSink sink, void* context)
{
    progressSink_ = sink;
    progressContext_ = context;
}

void RandomMapGenerator::ReportProgress(int percent)
{
    // sub_643C50 clamps the new value to the bar's maximum (its +72 field); the
    // bar spans 0..100 here (sub_642A60 was called with max 100.0).
    if (percent < 0)
        percent = 0;
    else if (percent > 100)
        percent = 100;

    progressPercent_ = percent;
    if (progressSink_)
        progressSink_(progressContext_, percent);
}

void RandomMapGenerator::Done()
{
    // ---- 0x59947E: the 100 % tick -----------------------------------------
    // sub_643C50(&dword_AC4F58, 0, 100.0, NAN) on the local path; the network
    // path would call sub_69AE90(199) instead.
    ReportProgress(100);

    // ---- 0x5994BA: the teardown, local path only ---------------------------
    // The vanilla hides dialog control 1592 and then runs
    //   sub_643C50(&progress, 0, 0.0, NAN)     the bar back to zero
    //   sub_643E70(&progress)                  progress->hWnd = 0 (detach)
    // There is no control to hide in the port; the two state changes map to:
    progressPercent_ = 0;                              // sub_643C50(0, 0.0)
    SetProgressSink(nullptr, nullptr);                 // sub_643E70
}

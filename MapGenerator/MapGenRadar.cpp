// ============================================================================
// MapGenRadar.cpp - the radar (mini-map) image.
//
// The reference implementation is FinalAlert 2's own minimap, NOT the engine's
// RadarClass. FA2 is what the finished .map gets opened in, so the preview has
// to look exactly like what FA2 draws for the same file. The three pieces of
// FA2 read here are CMapData::InitMinimap (MapData.cpp:6342),
// CMapData::GetMiniMapPos (MapData.h:756) and CMapData::Mini_UpdatePos
// (MapData.h:779).
//
// 1. THE IMAGE (InitMinimap)
//       pwidth  = GetWidth()  * 2
//       pheight = GetHeight()
//    i.e. the [Map] Size Width/Height written into the .map, each cell being
//    TWO pixels wide and ONE tall. The buffer starts out all white
//    ("memset(m_mini_colors.data(), 255, ...)") - not black.
//
// 2. THE PLACEMENT (GetMiniMapPos)
//    FA2 walks the whole isometric field, i and e over [0, IsoSize) with
//    IsoSize = Width + Height, and maps (i = X, e = Y) onto the DIB with
//
//       x = IsoSize - i + e                                (i = map X)
//       y = e / 2 + i / 2                                  (e = map Y)
//       tx = IsoSize - GetWidth() + GetHeight()
//       ty = GetHeight() / 2 + GetWidth() / 2
//       x -= tx;  y -= ty;
//       x += pheight;  y += pheight / 2;
//
//    which collapses to x = Width + Y - X and y = X/2 + Y/2 - Width/2, all in
//    integer arithmetic. FA2 stores the DIB bottom-up and then flips with
//    "y = pheight - y - 1"; this port keeps a top-down buffer, so the flip
//    cancels out and `y` above is the row directly. Cells outside the image are
//    dropped (FA2's "if (x >= pwidth || y >= pheight || x < 0 || y < 0) return").
//
//    The loop covers the SQUARE [0, IsoSize) x [0, IsoSize), not the map
//    diamond, so the cells outside the map are painted too - FA2 reads them as
//    ground 0 and draws them with tile 0's radar colours, which is what fills
//    the corners of the diamond.
//
// 3. THE COLOUR (Mini_UpdatePos)
//    Per cell: ground = wGround (0 for an empty cell), subt = bSubTile, and
//    then, out of the (tile, sub-tile) frame's TMP header,
//       left  pixel = rgbLeft   (+43 R, +44 G, +45 B)
//       right pixel = rgbRight  (+46 R, +47 G, +48 B)
//    No ratio is applied and nothing is halved - the six bytes go straight in
//    (XCC_GetTMPTileInfo, MissionEditorPackLib.cpp:631). A frame FA2 has no
//    art for is skipped whole ("if (subt >= wTileCount) return"), leaving the
//    white background.
//
//    Overlays then override both pixels, in this order (RA2_MODE):
//       green tiberium  (0x65 < ov <= 0x79 || 0x82 < ov < 0xA7)  RGB(250,250,0)
//       veins           (0x7E)                                   RGB(190,180,120)
//       vein hole/border(0xA7 / 0xB2)                            RGB(165,160,120)
//       any other overlay (ov != 0xFF)                           RGB( 20, 20, 20)
//
//    Finally the starting positions: a cell within a Chebyshev distance of 1
//    from a waypoint whose number is below 8 is painted red RGB(255,0,0).
//    FA2's building/unit/infantry house colours do not apply here - the port
//    generates terrain only and has no object list.
//
// The stage also writes the image into the output folder (Mapoutput) as
// radar_preview.png; the UI draws the same buffer in its preview panel (see
// WinMain.cpp).
// ============================================================================

#include "pch.h"
#include "MapGen.h"

#include <algorithm>
#include <vector>
#include <objidl.h>      // IStream / PROPID / byte - gdiplus.h needs these first
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

namespace {

// 0xAARRGGBB, the layout RadarImage::pixels uses.
uint32_t Rgb(unsigned char r, unsigned char g, unsigned char b)
{
    return 0xFF000000u | (static_cast<uint32_t>(r) << 16)
         | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
}

// FA2's ovrlinline.h:26 helper, verbatim.
bool IsGreenTiberium(int type)
{
    return (type > 0x65 && type <= 0x79) || (type > 0x82 && type < 0xA7);
}

// CLSID of a GDI+ encoder, by MIME type.
bool GetEncoderClsid(const wchar_t* mime, CLSID* clsid)
{
    UINT count = 0;
    UINT bytes = 0;
    if (Gdiplus::GetImageEncodersSize(&count, &bytes) != Gdiplus::Ok || bytes == 0)
        return false;

    std::vector<BYTE> buffer(bytes);
    Gdiplus::ImageCodecInfo* codecs =
        reinterpret_cast<Gdiplus::ImageCodecInfo*>(buffer.data());
    if (Gdiplus::GetImageEncoders(count, bytes, codecs) != Gdiplus::Ok)
        return false;

    for (UINT i = 0; i < count; ++i)
    {
        if (wcscmp(codecs[i].MimeType, mime) == 0)
        {
            *clsid = codecs[i].Clsid;
            return true;
        }
    }
    return false;
}

// Writes the image as a PNG. GDI+ is started and shut down around the call.
bool SaveRadarPng(const RadarImage& image, const wchar_t* path)
{
    if (image.Empty() || path == nullptr)
        return false;

    Gdiplus::GdiplusStartupInput input;
    ULONG_PTR token = 0;
    if (Gdiplus::GdiplusStartup(&token, &input, nullptr) != Gdiplus::Ok)
        return false;

    bool saved = false;
    {
        // The pixels are already 32-bpp BGRA, so the bitmap can wrap them.
        Gdiplus::Bitmap bitmap(
            image.width, image.height, image.width * 4, PixelFormat32bppARGB,
            reinterpret_cast<BYTE*>(const_cast<uint32_t*>(image.pixels.data())));

        CLSID encoder = {};
        if (bitmap.GetLastStatus() == Gdiplus::Ok
            && GetEncoderClsid(L"image/png", &encoder))
        {
            saved = (bitmap.Save(path, &encoder, nullptr) == Gdiplus::Ok);
        }
    }

    Gdiplus::GdiplusShutdown(token);
    return saved;
}

}   // namespace

void RandomMapGenerator::ComputeRadarImage()
{
    radarImage_ = RadarImage();

    if (cellSlots_ == nullptr || size_.mapWidth <= 0 || size_.mapHeight <= 0)
        return;

    // FA2 reads GetWidth()/GetHeight() out of the .map's [Map] Size, i.e. the
    // very numbers SaveMapFile writes - the port's mapWidth / mapHeight.
    const int width   = size_.mapWidth;
    const int height  = size_.mapHeight;
    const int isoSize = width + height;

    RadarImage image;
    image.width  = width * 2;                     // two pixels per cell
    image.height = height;
    image.pixels.assign(
        static_cast<size_t>(image.width) * static_cast<size_t>(image.height),
        0xFFFFFFFFu);                             // white, like FA2's memset 255

    // ---- the starting-point marks -----------------------------------------
    // FA2 paints red over every cell within a Chebyshev distance of 1 from a
    // waypoint below 8 (MapData.h:939 - the 3 x 3 scan around the cell).
    std::vector<uint8_t> startMark(
        static_cast<size_t>(isoSize) * static_cast<size_t>(isoSize), 0);
    for (size_t i = 0; i < startingPoints_.size(); ++i)
    {
        const StartingPointRecord& sp = startingPoints_[i];
        if (sp.index < 0 || sp.index >= 8)
            continue;

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                const int mx = sp.coords.X + dx;
                const int my = sp.coords.Y + dy;
                if (mx < 0 || my < 0 || mx >= isoSize || my >= isoSize)
                    continue;
                startMark[static_cast<size_t>(my) * isoSize + mx] = 1;
            }
        }
    }

    // ---- the field walk ----------------------------------------------------
    // i = map X, e = map Y, both over [0, isoSize) - FA2's Mini_UpdatePos loop.
    const int tx = isoSize - width + height;
    const int ty = height / 2 + width / 2;

    // [port-only] 水平镜像修正。FA2/游戏小地图按全量 iso 网格的坐标轴取色，
    // 本工程 IsoMapPack5 的记录流按紧凑菱形（512 行宽）排列，两套横轴在等距
    // 投影上关于图中轴互为镜像（主视图用记录内坐标定位故不受影响，仅小地图
    // 左右相反——2026-10-03 用出生点红点逐格实证）。以"格"为单位镜像：每个
    // 格仍是左像素 rgbLeft、右像素 rgbRight（TMP 帧头的左右半色不能随像素整
    // 行翻转而互换），只是格的落点从 px 搬到 2*(W-1)-px。
    const int mirrorBase = 2 * (width - 1);

    for (int e = 0; e < isoSize; ++e)
    {
        for (int i = 0; i < isoSize; ++i)
        {
            // GetMiniMapPos, term for term, so the integer truncation matches.
            int px = isoSize - i + e;
            int py = e / 2 + i / 2;
            px -= tx;
            py -= ty;
            px += height;
            py += height / 2;
            px = mirrorBase - px;                    // [port-only] 左右反转回来

            if (px < 0 || py < 0 || px >= image.width || py >= image.height)
                continue;

            // The cell, or the invalid sentinel outside the map. FA2 clamps
            // the ground index ("wGround >= tiledata_count ? 0 : wGround"), so
            // 0xFFFF - the port's "covered by a multi-cell tile" marker - as
            // well as any other out-of-range tile falls back to tile 0.
            const MapCell* cell = CellAt(i, e);

            int ground = cell->IsoTileTypeIndex;
            if (ground < 0 || ground >= static_cast<int>(tileCellAttrs_.size()))
                ground = 0;

            const TileCellAttr* attr = TileCellAttrAt(ground, cell->Height);
            if (attr == nullptr)                 // "subt >= wTileCount" -> skip
                continue;

            uint32_t left  = Rgb(attr->radarRedLeft, attr->radarGreenLeft,
                                 attr->radarBlueLeft);
            uint32_t right = Rgb(attr->radarRedRight, attr->radarGreenRight,
                                 attr->radarBlueRight);

            // The overlay overrides, in FA2's order. -1 is the port's "no
            // overlay", which FA2 spells 0xFF.
            const int overlay = (cell->OverlayTypeIndex < 0
                                 || cell->OverlayTypeIndex > 0xFF)
                              ? 0xFF : cell->OverlayTypeIndex;
            if (IsGreenTiberium(overlay))
            {
                left = right = Rgb(250, 250, 0);
            }
            else if (overlay == 0x7E)                        // OVRL_VEINS
            {
                left = right = Rgb(190, 180, 120);
            }
            else if (overlay == 0xA7 || overlay == 0xB2)     // VEINHOLE / BORDER
            {
                left = right = Rgb(165, 160, 120);
            }
            else if (overlay != 0xFF)
            {
                left = right = Rgb(20, 20, 20);
            }

            if (startMark[static_cast<size_t>(e) * isoSize + i] != 0)
                left = right = Rgb(255, 0, 0);

            const size_t row = static_cast<size_t>(py)
                             * static_cast<size_t>(image.width);
            image.pixels[row + static_cast<size_t>(px)] = left;
            // FA2 writes the second pixel right after the first and lets it
            // fall off the buffer only at the very end; here it is clipped to
            // the row, which keeps it out of the next row's first cell.
            if (px + 1 < image.width)
                image.pixels[row + static_cast<size_t>(px) + 1] = right;
        }
    }

    radarImage_ = image;

    // ---- write the PNG into the output folder ------------------------------
    // Same folder as the ".map": <工程根>\Mapoutput, i.e. two levels up from
    // the executable (x64\Debug\ / x64\Release\).
    wchar_t wdir[MAX_PATH];
    GetModuleFileNameW(nullptr, wdir, MAX_PATH);
    wchar_t* slash = wcsrchr(wdir, L'\\');
    if (slash)
        slash[1] = L'\0';

    wchar_t wdirOut[MAX_PATH];
    swprintf_s(wdirOut, L"%s..\\..\\Mapoutput\\", wdir);
    CreateDirectoryW(wdirOut, nullptr);   // 已存在时返回失败，忽略

    wchar_t wpath[MAX_PATH];
    swprintf_s(wpath, L"%s..\\..\\Mapoutput\\radar_preview.png", wdir);
    SaveRadarPng(radarImage_, wpath);
}
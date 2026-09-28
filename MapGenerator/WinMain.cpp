#include "pch.h"
#include <windows.h> // 需要包含 Win32 API 头文件
#include <strsafe.h>
#include "MapGen.h"
#include <cstdlib>  // rand/srand
#include <ctime>    // time

// CreateFontW/DeleteObject/SetBkColor在gdi32.lib，显式链接保险
#pragma comment(lib, "gdi32.lib")

// 控件ID
#define ID_GENERATE_BTN 101

#define ID_ENV_COMBO     110
#define ID_TIME_COMBO    111
#define ID_THEATER_COMBO 112
#define ID_SIZE_COMBO    113
#define ID_ORE_COMBO     114
#define ID_PLAYER_COMBO  115

// 玩家可调整的生成参数（除玩家数外均为下拉框选中项索引）
struct MapGenParams
{
    int environment;  // 环境：0大陆 1团队大陆 2内陆 3山地
    int timeOfDay;    // 时间：0早晨 1下午 2黄昏 3夜晚
    int theater;      // 剧场：0温带 1雪地
    int mapSize;       // 地图大小：0小 1中 2大 3特大
    int oreDensity;   // 资源：0低 1中 2高 3极高
    int playerIndex;  // 玩家数下拉框索引：0对应2人，6对应8人

    int PlayerCount() const { return playerIndex + 2; }
};

static const wchar_t* kEnvOptions[]     = { L"大陆", L"团队大陆", L"内陆", L"山地" };
static const wchar_t* kTimeOptions[]    = { L"早晨", L"下午", L"黄昏", L"夜晚" };
static const wchar_t* kTheaterOptions[] = { L"温带", L"雪地" };
static const wchar_t* kSizeOptions[]    = { L"小", L"中", L"大", L"特大" };
static const wchar_t* kOreOptions[]     = { L"低", L"中", L"高", L"极高" };
static const wchar_t* kPlayerOptions[]  = { L"2", L"3", L"4", L"5", L"6", L"7", L"8" };

// 每一行参数UI：标签 + 选项列表 + 下拉框控件ID
struct ParamRow
{
    const wchar_t* label;
    const wchar_t* const* options;
    int optionCount;
    int comboId;
};

static const ParamRow kParamRows[] =
{
    { L"环境",     kEnvOptions,     4, ID_ENV_COMBO },
    { L"时间",     kTimeOptions,    4, ID_TIME_COMBO },
    { L"剧场",     kTheaterOptions, 2, ID_THEATER_COMBO },
    { L"地图大小", kSizeOptions,    4, ID_SIZE_COMBO },
    { L"资源",     kOreOptions,     4, ID_ORE_COMBO },
    { L"玩家数",   kPlayerOptions,  7, ID_PLAYER_COMBO },
};

static HFONT g_uiFont = nullptr;

// 创建控件并统一套用字体
static HWND CreateCtl(HWND parent, const wchar_t* className, const wchar_t* text,
                      DWORD style, int x, int y, int w, int h, int id, HINSTANCE inst)
{
    HWND ctl = CreateWindowW(className, text, style, x, y, w, h,
                             parent, (HMENU)(INT_PTR)id, inst, nullptr);
    if (ctl && g_uiFont)
        SendMessageW(ctl, WM_SETFONT, (WPARAM)g_uiFont, TRUE);
    return ctl;
}

// 读取下拉框当前选中索引（异常情况按第0项处理）
static int ComboSel(HWND hWnd, int comboId)
{
    int sel = (int)SendDlgItemMessageW(hWnd, comboId, CB_GETCURSEL, 0, 0);
    return (sel == CB_ERR) ? 0 : sel;
}

// 从UI读取全部生成参数，之后生成器直接消费这个结构体即可
static MapGenParams ReadParams(HWND hWnd)
{
    MapGenParams p = {};
    p.environment = ComboSel(hWnd, ID_ENV_COMBO);
    p.timeOfDay   = ComboSel(hWnd, ID_TIME_COMBO);
    p.theater     = ComboSel(hWnd, ID_THEATER_COMBO);
    p.mapSize     = ComboSel(hWnd, ID_SIZE_COMBO);
    p.oreDensity  = ComboSel(hWnd, ID_ORE_COMBO);
    p.playerIndex = ComboSel(hWnd, ID_PLAYER_COMBO);
    return p;
}

// 将 UI 的 environment 索引映射为 RA2 的 LandType
// UI: 0=大陆, 1=团队大陆, 2=内陆, 3=山地
// LandType: 0=群岛, 1=大陆, 2=团队大陆, 3=内陆, 4=山地
static LandType EnvToLandType(int envIndex)
{
    switch (envIndex)
    {
    case 0: return LandType::Continent;
    case 1: return LandType::TeamContinent;
    case 2: return LandType::Inland;
    case 3: return LandType::Mountainous;
    default: return LandType::Continent;
    }
}

static const wchar_t* LandTypeStr(LandType lt)
{
    switch (lt)
    {
    case LandType::Archipelago:   return L"群岛";
    case LandType::Continent:     return L"大陆";
    case LandType::TeamContinent: return L"团队大陆";
    case LandType::Inland:        return L"内陆";
    case LandType::Mountainous:   return L"山地";
    default: return L"未知";
    }
}

// 点击"生成"：读取参数 → 调用地形生成主体 → 回显结果
static void OnGenerate(HWND hWnd)
{
    MapGenParams p = ReadParams(hWnd);

    // 组装生成配置（对应 RandomMapGenerator 关键字段）
    MapGenConfig cfg = {};
    cfg.landType    = EnvToLandType(p.environment);
    cfg.theater     = p.theater;
    cfg.timeOfDay   = p.timeOfDay;
    cfg.sizeSlider  = p.mapSize;     // 尺寸滑块 0-3
    cfg.playerCount = p.PlayerCount(); // 玩家数 2-8
    cfg.oreDensity  = p.oreDensity;

    // 随机种子（对应 WM_USER+1175 初始化时的 RandomRanged(0, 0xFFFF)）
    srand((unsigned)time(nullptr));
    cfg.randomSeed = (uint32_t)(rand() & 0xFFFF);

    // 水量 roll（对应 sub_597260 @ 0x597282）：
    //   this[19] = RandomRanged(水量下限表[地形], 水量上限表[地形])
    // 原版在随机地图对话框参数变化时按当前地形重新 roll（sub_596C70 @ 0x596E08
    // 调用，a2 = this[15] 即地形类型），用的是全局随机器 this_pRandomizer，
    // 与生成主 RNG dst_ 无关——不消耗 dst_ 的随机序列。这里在生成前用 CRT rand
    // roll 一次，范围与原版一致：
    //   群岛 [75,100]  大陆 [0,25]  团队大陆 [50,100]  内陆 [0,100]  山地 [0,100]
    // roll 出 0 时内陆/山地走"全陆地"分支（对应原版 this[19]==0 跳过 sub_59C580）。
    static const int kWaterMin[5] = { 75, 0, 50, 0, 0 };         // 0x82B0A8
    static const int kWaterMax[5] = { 100, 25, 100, 100, 100 };  // 0x82B0BC
    int lt = static_cast<int>(cfg.landType);
    cfg.waterAmount = kWaterMin[lt] + rand() % (kWaterMax[lt] - kWaterMin[lt] + 1);

    // 调用地形生成主体（对应 sub_599650）
    RandomMapGenerator rmg;
    bool ok = rmg.GenerateMapBody(cfg);

    // 地形生成分派（对应 sub_598960 @ 0x598aed - 0x598b0d）：
    //   LandType 3/4 且水量(this[19])非零 → sub_59C580 特殊地形（骨架）
    //   其余                              → sub_59A6C0 常规地形（第 1/2 段）
    wchar_t pathText[160];
    StringCchCopyW(pathText, ARRAYSIZE(pathText), L"未执行");
    if (ok)
    {
        if (cfg.landType == LandType::Inland || cfg.landType == LandType::Mountainous)
        {
            if (rmg.GetWaterAmount() != 0)
            {
                rmg.GenerateSpecialTerrain();   // sub_59C580
                StringCchPrintfW(pathText, ARRAYSIZE(pathText),
                    L"sub_59C580 特殊地形（骨架，水量=%d）", rmg.GetWaterAmount());
            }
            else
            {
                StringCchCopyW(pathText, ARRAYSIZE(pathText),
                    L"跳过（水量=0，全陆地图）");
            }
        }
        else
        {
            rmg.GenerateTerrain();              // sub_59A6C0
            StringCchPrintfW(pathText, ARRAYSIZE(pathText),
                L"sub_59A6C0 常规地形（淹水 %d 格）", rmg.GetCellCount());
        }
    }

    wchar_t text[1024];
    if (!ok)
    {
        StringCchPrintfW(text, ARRAYSIZE(text), L"地形生成失败！");
    }
    else
    {
        const MapSizeResult& sz = rmg.GetSize();
        const RMGSettings& st = rmg.GetSettings();

        // 当前剧场+时间对应的矿灯名（原版按时间索引 4 个建筑名）
        const std::vector<std::string>& lamps =
            p.theater ? st.SnowOrePatchLamps : st.TemperateOrePatchLamps;
        const char* lampName =
            (p.timeOfDay < (int)lamps.size()) ? lamps[p.timeOfDay].c_str() : "(无)";

        StringCchPrintfW(text, ARRAYSIZE(text),
            L"=== 地形主体生成成功 ===\n"
            L"地形：%s\n"
            L"剧场：%s\n"
            L"时间：%s\n"
            L"玩家数：%d\n"
            L"尺寸档位：%s\n"
            L"地图宽：%d 格\n"
            L"地图高：%d 格\n"
            L"工作数组边长：%d\n"
            L"工作单元数：%d\n"
            L"25%%随机标志：%s\n"
            L"地形路径：%s\n"
            L"随机种子：0x%04X\n"
            L"\n--- RMGMD.INI 配置（sub_5981F0）---\n"
            L"配置来源：%s\n"
            L"矿量下限/上限：%d / %d\n"
            L"最大树木数：%d\n"
            L"光照等级（当前时间）：%d（%d/100）\n"
            L"环境光（当前剧场+时间）：%d\n"
            L"植被密度（当前地形）：%d - %d\n"
            L"矿区灯（当前剧场+时间）：%hs",
            LandTypeStr(cfg.landType),
            kTheaterOptions[p.theater],
            kTimeOptions[p.timeOfDay],
            cfg.playerCount,
            kSizeOptions[p.mapSize],
            sz.width, sz.height,
            sz.workSide,
            sz.workSide * sz.workSide,
            rmg.GetRandom25Flag() ? L"是" : L"否",
            pathText,
            cfg.randomSeed,
            rmg.GetIniLoaded() ? L"RMGMD.INI" : L"内置默认值",
            st.MinTiberium, st.MaxTiberium,
            st.MaxTrees,
            st.LevelLight(p.timeOfDay), st.LevelLight(p.timeOfDay),
            st.AmbientLight(p.theater, p.timeOfDay),
            st.VegetationMin((int)cfg.landType), st.VegetationMax((int)cfg.landType),
            lampName);
    }

    MessageBoxW(hWnd, text, L"生成结果", MB_OK | MB_ICONINFORMATION);
}

// 窗口过程（处理窗口消息，比如按钮点击）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        CREATESTRUCTW* cs = (CREATESTRUCTW*)lParam;

        // 统一字体：默认系统字体的中文渲染发虚，换成微软雅黑
        g_uiFont = CreateFontW(-15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Microsoft YaHei UI");

        // 逐行创建“标签 + 下拉框”参数UI
        for (int i = 0; i < ARRAYSIZE(kParamRows); ++i)
        {
            const ParamRow& row = kParamRows[i];
            int y = 22 + i * 36;

            CreateCtl(hWnd, L"Static", row.label,
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
                28, y, 84, 26, 0, cs->hInstance);

            HWND combo = CreateCtl(hWnd, L"ComboBox", nullptr,
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,
                124, y, 240, 200, row.comboId, cs->hInstance);
            // 注意：ComboBox的高度参数包含下拉展开后的列表高度，200保证7项全部可见

            for (int j = 0; j < row.optionCount; ++j)
                SendMessageW(combo, CB_ADDSTRING, 0, (LPARAM)row.options[j]);
            SendMessageW(combo, CB_SETCURSEL, 0, 0); // 默认选中第一项
        }

        CreateCtl(hWnd, L"Button", L"生成",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
            152, 252, 120, 40, ID_GENERATE_BTN, cs->hInstance);
        break;
    }
    case WM_CTLCOLORSTATIC:
        // 静态标签默认背景是灰色按钮底色，这里改成与窗口一致的白色
        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
        return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
    case WM_COMMAND:
    {
        // 处理按钮点击事件
        if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == ID_GENERATE_BTN)
        {
            OnGenerate(hWnd);
        }
        break;
    }
    case WM_DESTROY:
        if (g_uiFont)
        {
            DeleteObject(g_uiFont);
            g_uiFont = nullptr;
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
    // 1. 注册窗口类
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc;          // 绑定窗口过程
    wc.hInstance = hInstance;          // 当前实例
    wc.lpszClassName = L"MapGeneratorWindowClass"; // 窗口类名
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassW(&wc)) return 1;

    // 2. 创建主窗口
    HWND hWnd = CreateWindowW(
        L"MapGeneratorWindowClass",    // 类名
        L"地图生成器",                  // 窗口标题
        WS_OVERLAPPEDWINDOW,           // 窗口样式
        CW_USEDEFAULT, CW_USEDEFAULT,  // 默认位置
        440, 400,                      // 窗口大小（容纳6行参数+按钮）
        NULL, NULL, hInstance, NULL
    );

    if (!hWnd) return 1;

    // 3. 显示窗口并更新
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // 4. 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

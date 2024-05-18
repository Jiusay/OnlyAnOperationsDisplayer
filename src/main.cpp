#include <Windows.h>
#include <map>
#include <string>
#include <CommCtrl.h>
#include <windowsx.h>
#include <fstream>
#include <ShlObj.h>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

#include "lang.h"
#include "myuihelper.h"
#include "mainproc.h"

map<string, wstring> language_table;

int main() {
    //DPI Aware
    SetProcessDPIAware();
	//Register class
	WNDCLASSEXW wc = { 0 };
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"OnlyAnOperationsDisplayerMainWndClassName";
    wc.lpfnWndProc = TFSRMainWindowProc;
    wc.style = CS_DBLCLKS;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hIcon = LoadIconW(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    if (!RegisterClassExW(&wc)) {
        MessageBoxW(NULL, language_table["lng.tip.fail_to_register"].c_str(), L"", MB_OK | MB_ICONERROR);
        exit(1);
    }
    //Create window
    HINSTANCE hi = GetModuleHandle(nullptr);
    POINT cursor = { 0,0 }; GetCursorPos(&cursor);
    HWND wnd = CreateWindowExW(0, L"OnlyAnOperationsDisplayerMainWndClassName",
        L"Only an operations displayer",
        ((WS_OVERLAPPEDWINDOW | WS_VISIBLE) & (~(WS_MAXIMIZEBOX | WS_SIZEBOX))/*No maximze button and size*/),
        cursor.x - 250, cursor.y - 125,
        500, 250,
        HWND_DESKTOP,
        nullptr,
        hi,
        nullptr);
    if (wnd == nullptr) {
        MessageBoxW(NULL, language_table["lng.tip.fail_to_create_wnd"].c_str(), L"", MB_OK | MB_ICONERROR);
        exit(1);
    }

    //Create controls
    HWND hctrl = nullptr;
    CreateWindowExW(0, L"Static",
        L"语言|Language",
        WS_VISIBLE | WS_CHILD,
        5, 180,
        140, 20,
        wnd,
        (HMENU)1000,
        hi,
        nullptr);

    hctrl = CreateWindowExW(0, L"ComboBox",
        L"",
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,
        160, 180,
        250, 20,
        wnd,
        (HMENU)1006,
        hi,
        nullptr);

    ComboBox_AddString(hctrl, L"简体中文");
    ComboBox_AddString(hctrl, L"English");
    wchar_t buffer[512] = { 0 };
    SHGetSpecialFolderPathW(nullptr, buffer, CSIDL_APPDATA, TRUE);
    wstring path(wstring(buffer) + L"\\Jiusay\\");
    wifstream in(path + L"curlt.txt");
    if (!in) {
        MessageBoxFormatW(MB_OK | MB_ICONWARNING,
            L"",
            wnd,
            L"无法打开语言配置文件\n %s \n程序将使用内置的简体中文作为显示语言",
            (path + L"curlt.txt").c_str());
        CreateDefaultLanguageTable(language_table);
        CreateDirectoryW(path.c_str(), nullptr);
        wofstream wf(path + L"curlt.txt",ios::out | ios::trunc);
        if (wf.is_open()) {
            wf << L"<zhCN>";
        }
        wf.close();
    }
    else {
        ZeroMemory(buffer, sizeof(wchar_t) * 512);
        in.read(buffer, 512);
        if (wcscmp(buffer, L"<zhCN>") == 0) { 
            CreateDefaultLanguageTable(language_table); 
            ComboBox_SetCurSel(hctrl, 0);
        }
        else if (wcscmp(buffer, L"<enUS>") == 0){
            CreateDefaultLanguageTable2(language_table);
            ComboBox_SetCurSel(hctrl, 1);
        }
    }
    in.close();
    

    CreateWindowExW(0, L"Button",
        language_table["lng.txt.topmost"].c_str(),
        BS_CHECKBOX | BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        5, 5,
        490, 20,
        wnd,
        (HMENU)1001,
        hi,
        nullptr);

    CreateWindowExW(0, L"Button",
        language_table["lng.txt.minimze_in_using_other_wnd"].c_str(),
        BS_CHECKBOX | BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        5, 26,
        490, 20,
        wnd,
        (HMENU)1002,
        hi,
        nullptr);

    CreateWindowExW(0, L"Button",
        language_table["lng.txt.show_keys"].c_str(),
        BS_CHECKBOX | BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        5, 55,
        490, 20,
        wnd,
        (HMENU)1003,
        hi,
        nullptr);

    CreateWindowExW(0, L"Button",
        language_table["lng.txt.sk_without_entrying"].c_str(),
        BS_CHECKBOX | BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_DISABLED,
        5, 76,
        490, 20,
        wnd,
        (HMENU)1004,
        hi,
        nullptr);

    CreateWindowExW(0, L"Static",
        language_table["lng.txt.floatingw_size"].c_str(),
        WS_VISIBLE | WS_CHILD,
        5, 97,
        490, 20,
        wnd,
        (HMENU)1000,
        hi,
        nullptr);

    hctrl = CreateWindowExW(0, L"msctls_trackbar32",
        L"",
        TBS_BOTH | TBS_NOTICKS | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        5, 118,
        490, 20,
        wnd,
        (HMENU)1005,
        hi,
        nullptr);
    SendMessageW(hctrl, TBM_SETRANGE, TRUE, MAKELPARAM(6, 18));

    //Init font
    HFONT font = nullptr;
    NONCLIENTMETRICSW info = { 0 };
    info.cbSize = sizeof(NONCLIENTMETRICSW);
    if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, 0, &info, 0)) {
        font = CreateFontIndirectW((LOGFONT*)&info.lfMessageFont);
    }
    EnumChildWindows(wnd, [](HWND h, LPARAM l)->BOOL {
        SendMessageW(h, WM_SETFONT, (WPARAM)l, 0);
        return TRUE;
        }, (LPARAM)font);

    UpdateWindow(wnd);

    //Pass the poniter of language table
    PostMessageW(wnd, (WM_USER + 1), (WPARAM)&language_table, (LPARAM)&language_table);

    //Message
    MSG messages;

    while (GetMessageW(&messages,NULL,0,0))
    {
        TranslateMessage(&messages);
        DispatchMessageW(&messages);
    }

    //User quited
    UnregisterClassW(L"ToolsForScreenRecordingMWClass", hi);
    return (int)messages.wParam;
}

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
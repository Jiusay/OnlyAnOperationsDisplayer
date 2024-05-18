#include <Windows.h>
#include <map>
#include <string>
#include <CommCtrl.h>
#include <windowsx.h>
#include <ShlObj.h>
#include <fstream>
#include "myuihelper.h"
#include "gk.h"
#include "resource.h"
#include "skproc.h"
#include "mousebgwnd.h"
using namespace std;

LRESULT CALLBACK TFSRMainWindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam) {
	//Poniter of language table
	static map<string, wstring>* ltp = nullptr;
	//HWNDs
	static HWND skwnd = nullptr;
	static HWND self = nullptr;
	static HWND mbgwnd = nullptr;

	static HHOOK hmouseh = nullptr;

	switch (message)
	{
	case WM_CREATE:
		self = hWnd;
		return 0;
	case (WM_USER + 1):
		ltp = (decltype(ltp))wParam;
		return 0;
	case (WM_USER + 2):
		skwnd = (decltype(skwnd))wParam;
		return 0;
	case (WM_USER + 3):
		mbgwnd = (decltype(mbgwnd))lParam;
		return 0;
	case WM_DPICHANGED:
		SetProcessDPIAware();
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_ACTIVATE:
		if (IsDlgButtonChecked(hWnd, 1002)/*check box of minimze in using other window*/ == BST_CHECKED &&
			wParam != WA_ACTIVE && wParam != WA_CLICKACTIVE)
			ShowWindow(hWnd, SW_MINIMIZE);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1001://Check topmost
			if (IsDlgButtonChecked(hWnd, 1001) == BST_CHECKED) {
				SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			else {
				SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			return 0;
		case 1003://Show keys
			if (IsDlgButtonChecked(hWnd, 1003) == BST_CHECKED) {
				//SetHook
				HHOOK hk = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHook, GetModuleHandle(nullptr), 0);
				if (hk == NULL) {
					wchar_t buffer[128] = { 0 };
					FormatMessageW(
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						nullptr,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						buffer,
						MAX_PATH,
						nullptr
					);
					MessageBoxFormatW(MB_OK | MB_ICONERROR,
						L"",
						hWnd,
						ltp->operator[]("lng.tip.fail_to_open").c_str(),
						buffer);
					return 0;
				}
				EnableWindow(GetDlgItem(hWnd, 1004/*Without entrying*/), TRUE);
				DialogBoxParamW(GetModuleHandle(nullptr),
					MAKEINTRESOURCEW(IDD_KeysShowingWnd),
					nullptr,
					SKWindowProc,
					(LPARAM)self);
				UnhookWindowsHookEx(hk);
				//Unhook
			}
			else {
				CheckDlgButton(hWnd, 1004, BST_UNCHECKED);
				EnableWindow(GetDlgItem(hWnd, 1004/*Without inputting*/), FALSE);
				PostMessageW(skwnd, WM_CLOSE, 0, 0);
				skwnd = nullptr;
			}
			return 0;
		case 1007:
			if (IsDlgButtonChecked(hWnd, 1007) == BST_CHECKED) {
				EnableWindow(GetDlgItem(hWnd, 1008), TRUE);
				HHOOK hk = SetWindowsHookExW(WH_MOUSE_LL, MouseHook, GetModuleHandle(nullptr), 0);
				DialogBoxParamW(GetModuleHandle(nullptr),
					MAKEINTRESOURCEW(IDD_MouseShowingBg),
					nullptr,
					MBGWindowProc,
					(LPARAM)hWnd);
				UnhookWindowsHookEx(hk);
			}
			else {
				EnableWindow(GetDlgItem(hWnd, 1008), FALSE);
				CheckDlgButton(hWnd, 1008, BST_UNCHECKED);
				PostMessageW(mbgwnd, WM_CLOSE, 0, 0);
			}
			return 0;
		default:
			break;
		}
		if (wParam == MAKEWPARAM(1006, CBN_SELCHANGE)) {
			int index = (int)ComboBox_GetCurSel(GetDlgItem(hWnd, 1006));
			wchar_t buffer[512] = { 0 };
			SHGetSpecialFolderPathW(nullptr, buffer, CSIDL_APPDATA, TRUE);
			wstring path(wstring(buffer) + L"\\Jiusay\\");
			wofstream wf(path + L"curlt.txt",ios::out | ios::trunc);
			if (index == 0) {
				wf << L"<zhCN>";
			}if (index == 1) {
				wf << L"<enUS>";
			}
			wf.close();
			if (MessageBoxW(hWnd, ltp->operator[]("lng.tip.lng_changed").c_str(),
				L"", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				char* cmdline = GetCommandLineA();
				if (!(cmdline != nullptr && WinExec(cmdline,SW_SHOW) > 31)) {
					MessageBoxW(hWnd,
						ltp->operator[]("lng.tip.fail_to_restart").c_str(),
						L"", MB_OK | MB_ICONWARNING);
				}
				else {
					exit(0);
				}
			}
		}
		return 0;
	case WM_HSCROLL:
	{
		LONG val = (LONG)SendMessageW(GetDlgItem(hWnd, 1005), TBM_GETPOS, 0, 0);
		if (skwnd != nullptr)
			PostMessageW(skwnd, (WM_USER + 3), (WPARAM)val, 0);
	}
		return 0;
	default:
		break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}
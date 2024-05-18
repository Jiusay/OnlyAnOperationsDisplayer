#include <Windows.h>
#include <CommCtrl.h>
#include "resource.h"

HWND skwnd = nullptr;

LRESULT CALLBACK KeyboardHook(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	KBDLLHOOKSTRUCT* info = (decltype(info))lParam;
	if(nCode >= 0 && (info->flags == 0 || info->flags == 1))
	PostMessageW(skwnd, (WM_USER + 1), (WPARAM)info->vkCode, 0);
	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

INT_PTR CALLBACK SKWindowProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static short show_timer = 0;
	static HWND mw = nullptr;
	static RECT lastpos = { 0,0,0,0 };
	switch (message)
	{
	case WM_CLOSE:
		GetWindowRect(hDlg, &lastpos);
		EndDialog(hDlg, 0);
		return 0;
	case WM_INITDIALOG:
		mw = (HWND)lParam;
		if (lastpos.left == 0 && lastpos.top == 0) {
			POINT cp;
			GetCursorPos(&cp);
			SetWindowPos(hDlg, HWND_TOPMOST, cp.x, cp.y, 0, 0, SWP_NOSIZE);
		}
		else {
			SetWindowPos(hDlg, HWND_TOPMOST, lastpos.left, lastpos.top, 0, 0, SWP_NOSIZE);
		}
	{
		LONG val = (LONG)SendMessageW(GetDlgItem(mw, 1005), TBM_GETPOS, 0, 0);

		HFONT font = nullptr;
		NONCLIENTMETRICSW info = { 0 };
		info.cbSize = sizeof(NONCLIENTMETRICSW);
		if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, 0, &info, 0)) {
			((LOGFONTW*)&info.lfMessageFont)->lfHeight += (abs(val) * 7);
			font = CreateFontIndirectW((LOGFONTW*)&info.lfMessageFont);
		}
		EnumChildWindows(hDlg, [](HWND h, LPARAM l)->BOOL {
			SendMessageW(h, WM_SETFONT, (WPARAM)l, 0);
			return TRUE;
			}, (LPARAM)font);

		SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 60 + ((int)val * 23.5), 20 + ((int)val * 5.5), SWP_NOMOVE);
		SetWindowPos(GetDlgItem(hDlg,IDC_Ks), NULL, 0, 0, 60 + ((int)val * 23.5), 20 + ((int)val * 5.5), SWP_NOMOVE);
	}
		SetTimer(hDlg, 1, 500, nullptr);
		skwnd = hDlg;
		PostMessageW((HWND)lParam, (WM_USER + 2), (WPARAM)hDlg, (LPARAM)hDlg);
		SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		return 0;
		//drag
	case WM_LBUTTONDOWN:
		SystemParametersInfoW(SPI_SETDRAGFULLWINDOWS, true, NULL, 0);
		DefWindowProcW(hDlg, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		return 0;
	case WM_TIMER:
		if (wParam == 1) {
			if (show_timer > 0)show_timer -= 1;
			else SetDlgItemTextW(hDlg, IDC_Ks, L"");
		}
		return 0;
		//kbd msg
	case (WM_USER + 1):
		show_timer = 3;
		switch ((DWORD)wParam)
		{
		case VK_TAB:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Tab");
			break;
		case VK_LSHIFT:case VK_RSHIFT:case VK_SHIFT:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Shift");
			break;
		case VK_LCONTROL:case VK_RCONTROL:case VK_CONTROL:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Ctrl");
			break;
		case VK_BACK:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Backspace");
			break;
		case VK_F1:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F1");
			break;
		case VK_F2:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F2");
			break;
		case VK_F3:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F3");
			break;
		case VK_F4:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F4");
			break;
		case VK_F5:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F5");
			break;
		case VK_F6:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F6");
			break;
		case VK_F7:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F7");
			break;
		case VK_F8:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F8");
			break;
		case VK_F9:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F9");
			break;
		case VK_F10:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F10");
			break;
		case VK_F11:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F11");
			break;
		case VK_F12:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F12");
			break;
		case VK_F13:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F13");
			break;
		case VK_F14:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F14");
			break;
		case VK_F15:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F15");
			break;
		case VK_F16:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F16");
			break;
		case VK_F17:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F17");
			break;
		case VK_F18:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F18");
			break;
		case VK_F19:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F19");
			break;
		case VK_F20:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F20");
			break;
		case VK_F21:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F21");
			break;
		case VK_F22:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F22");
			break;
		case VK_F23:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F23");
			break;
		case VK_F24:
			SetDlgItemTextW(hDlg, IDC_Ks, L"F24");
			break;
		case VK_UP:
			SetDlgItemTextW(hDlg, IDC_Ks, L"¡ü");
			break;
		case VK_DOWN:
			SetDlgItemTextW(hDlg, IDC_Ks, L"¡ý");
			break;
		case VK_LEFT:
			SetDlgItemTextW(hDlg, IDC_Ks, L"¡û");
			break;
		case VK_RIGHT:
			SetDlgItemTextW(hDlg, IDC_Ks, L"¡ú");
			break;
		case VK_ESCAPE:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Esc");
			break;
		case 13://Enter
			SetDlgItemTextW(hDlg, IDC_Ks, L"Enter");
			break;
		case VK_MENU:case VK_RMENU:case VK_LMENU://Alt
			SetDlgItemTextW(hDlg, IDC_Ks, L"Alt");
			break;
		case 20://Caps Lock
			SetDlgItemTextW(hDlg, IDC_Ks, L"CapsLock");
			break;
		case VK_INSERT:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Insert");
			break;
		case VK_DELETE:
			SetDlgItemTextW(hDlg, IDC_Ks, L"Delete");
			break;
		case 189://-
			SetDlgItemTextW(hDlg, IDC_Ks, L"-");
			break;
		case 187://=
			SetDlgItemTextW(hDlg, IDC_Ks, L"=");
			break;
		case 219://[
			SetDlgItemTextW(hDlg, IDC_Ks, L"[");
			break;
		case 221://]
			SetDlgItemTextW(hDlg, IDC_Ks, L"]");
			break;
		case 186://;
			SetDlgItemTextW(hDlg, IDC_Ks, L";");
			break;
		case 222://'
			SetDlgItemTextW(hDlg, IDC_Ks, L"'");
			break;
		case 188://,
			SetDlgItemTextW(hDlg, IDC_Ks, L",");
			break;
		case 190://.
			SetDlgItemTextW(hDlg, IDC_Ks, L".");
			break;
		case 191:///
			SetDlgItemTextW(hDlg, IDC_Ks, L"/");
			break;
		case 220://\

			SetDlgItemTextW(hDlg, IDC_Ks, L"\\");
			break;
		case 91:case 92://Windows
			SetDlgItemTextW(hDlg, IDC_Ks, L"Windows");
			break;
		case 33://PageUp
			SetDlgItemTextW(hDlg, IDC_Ks, L"PageUp");
			break;
		case 34://PageDown
			SetDlgItemTextW(hDlg, IDC_Ks, L"PageDown");
			break;
		case 35://End
			SetDlgItemTextW(hDlg, IDC_Ks, L"End");
			break;
		case 36://Home
			SetDlgItemTextW(hDlg, IDC_Ks, L"Home");
			break;
		case 32://Space
			SetDlgItemTextW(hDlg, IDC_Ks, L"Space");
			break;

		default:
		{
			wchar_t buffer[32] = { 0 };
			wsprintfW(buffer, L"%hc", (wchar_t)wParam);
			SetDlgItemTextW(hDlg, IDC_Ks, buffer);
		}
			break;
		}
		break;
	case (WM_USER + 3):
		SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 60 + ((int)wParam * 23.5), 20 + ((int)wParam * 5.5), SWP_NOMOVE);
		SetWindowPos(GetDlgItem(hDlg, IDC_Ks), NULL, 0, 0, 60 + ((int)wParam * 23.5), 20 + ((int)wParam * 5.5), SWP_NOMOVE);
		{
			HFONT font = nullptr;
			NONCLIENTMETRICSW info = { 0 };
			info.cbSize = sizeof(NONCLIENTMETRICSW);
			if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, 0, &info, 0)) {
				((LOGFONTW*)&info.lfMessageFont)->lfHeight += (abs((int)wParam) * 7);
				font = CreateFontIndirectW((LOGFONTW*)&info.lfMessageFont);
			}
			EnumChildWindows(hDlg, [](HWND h, LPARAM l)->BOOL {
				SendMessageW(h, WM_SETFONT, (WPARAM)l, 0);
				return TRUE;
				}, (LPARAM)font);
		}
		break;
	default:
		break;
	}
	return 0;
}
#include <Windows.h>
HWND mbgwnd = nullptr, mainw = nullptr;
LRESULT CALLBACK MouseHook(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	if (nCode >= 0) {
		MOUSEHOOKSTRUCTEX* info = (decltype(info))lParam;
		RECT wr = { 0,0,0,0 }; GetWindowRect(mbgwnd, &wr);
		SetWindowPos(mbgwnd,
			nullptr,
			info->pt.x - (wr.right - wr.left) / 2,
			info->pt.y - (wr.bottom - wr.top) / 2,
			0, 0,
			SWP_NOSIZE | SWP_NOACTIVATE);
		if (IsDlgButtonChecked(mainw, 1008) == BST_CHECKED &&
			(wParam == 513 || wParam == 516))
			PostMessageW(mbgwnd, (WM_USER + 1), 0, 0);
	}
	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

INT_PTR CALLBACK MBGWindowProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static short reset_timer = 0;
	static COLORREF color = RGB(100, 100, 255);
	switch (message)
	{
	case (WM_USER + 1):
		color = RGB(255, 255, 100);
		reset_timer = 2;
		InvalidateRect(hDlg, nullptr, TRUE);
		break;
	case WM_INITDIALOG:
	{
		RECT wr; GetWindowRect(hDlg, &wr);
		HRGN rgn = CreateEllipticRgn(0, 0, (wr.right - wr.left), (wr.bottom - wr.top));
		SetWindowRgn(hDlg, rgn, TRUE);
	}
		mbgwnd = hDlg;
		mainw = (HWND)lParam;
		SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		PostMessageW((HWND)lParam, (WM_USER + 3), (WPARAM)hDlg, (LPARAM)hDlg);
		SetWindowLongW(hDlg, GWL_EXSTYLE,
			(GetWindowLongW(hDlg, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT));
		SetLayeredWindowAttributes(hDlg, 0, 180, LWA_ALPHA);
		{
			HDC dc = GetWindowDC(hDlg);
			HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
			RECT r = { 0,0,0,0 }; GetClientRect(hDlg, &r);
			FillRect(dc, &r, brush);
			ReleaseDC(hDlg, dc);
			DeleteObject(brush);
		}
		SetTimer(hDlg, 1, 50, nullptr);
		return 0;
	case WM_TIMER:
		if (wParam == 1) {
			if (reset_timer > 0) { reset_timer -= 1; }
			else { color = RGB(100, 100, 255); InvalidateRect(hDlg, nullptr, TRUE); }
		}
		break;
	case WM_ACTIVATE:
		if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)return 1;
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return 0;
	case WM_ERASEBKGND:
	{
		HDC hdc = (HDC)wParam;
		RECT rect;
		GetClientRect(hDlg, &rect);

		HBRUSH brush = CreateSolidBrush(color);
		FillRect(hdc, &rect, brush);
		DeleteObject(brush);
		return TRUE;
	}
		break;
	default:
		break;
	}
	return 0;
}
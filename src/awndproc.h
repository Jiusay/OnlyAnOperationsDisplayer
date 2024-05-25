#pragma once
INT_PTR CALLBACK AppearanceWindowProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
struct ColorChosenStatus
{
	UINT flag = 0;
	COLORREF selected = 0;
};
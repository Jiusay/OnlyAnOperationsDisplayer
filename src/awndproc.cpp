#include <Windows.h>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "ShlObj.h"
#include "awndproc.h"
#include "resource.h"
#include "myuihelper.h"
using namespace std;

map<string, wstring>* GetLanguageTablePtr();

INT_PTR CALLBACK AppearanceWindowProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static vector<HBRUSH> bgcs;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hctrl = nullptr;
		SetWindowLongW((hctrl = GetDlgItem(hDlg, IDC_KDC)), GWL_STYLE,
			(GetWindowLongW(hctrl, GWL_STYLE) | SS_NOTIFY | SS_CENTERIMAGE));
		SetWindowLongW((hctrl = GetDlgItem(hDlg, IDC_MDC)), GWL_STYLE,
			(GetWindowLongW(hctrl, GWL_STYLE) | SS_NOTIFY | SS_CENTERIMAGE));
		SetWindowLongW((hctrl = GetDlgItem(hDlg, IDC_MDL)), GWL_STYLE,
			(GetWindowLongW(hctrl, GWL_STYLE) | SS_NOTIFY | SS_CENTERIMAGE));
		map<string, wstring>* lt = (decltype(lt))GetLanguageTablePtr();
		if(lt->count("lng.txt.appearance") >= 1)SetWindowTextW(hDlg, lt->operator[]("lng.txt.appearance").c_str());
		EnumChildWindows(hDlg, [](HWND hctrl, LPARAM ltp)->BOOL {
			char lid[256] = { 0 };
			GetWindowTextA(hctrl, lid, 255);
			string lids(lid);
			map<string, wstring>* rltp = (decltype(rltp))ltp;
			if (rltp->count(lids) >= 0)SetWindowTextW(hctrl, rltp->operator[](lids).c_str());
			return TRUE;
			}, (LPARAM)lt);

		HFONT font = nullptr;
		NONCLIENTMETRICSW info = { 0 };
		info.cbSize = sizeof(NONCLIENTMETRICSW);
		if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, 0, &info, 0)) {
			font = CreateFontIndirectW((LOGFONT*)&info.lfMessageFont);
		}
		EnumChildWindows(hDlg, [](HWND h, LPARAM l)->BOOL {
			SendMessageW(h, WM_SETFONT, (WPARAM)l, 0);
			return TRUE;
			}, (LPARAM)font);
	}
	break;
	case WM_CLOSE:
		for (auto it = bgcs.begin(); it != bgcs.end(); it++)DeleteObject(*it);
		bgcs.clear();
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_KDC) {
			unsigned char colors[3] = { 0, 0, 0};
			wchar_t datapath[512] = { 0 };
			SHGetSpecialFolderPathW(nullptr, datapath, CSIDL_APPDATA, TRUE);
			wsprintfW(datapath, L"%s%s", datapath, L"\\Jiusay\\kbg_bgc.dat");
			CHOOSECOLORW cci = { 0 };

			ifstream rf(datapath);
			rf.read((char*)colors, 3);
			rf.close();
			cci.rgbResult = RGB(colors[0], colors[1], colors[2]);

			cci.lStructSize = sizeof(CHOOSECOLORW);
			cci.hwndOwner = hDlg;
			cci.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
			COLORREF arr[16] = { 0 };
			cci.lpCustColors = arr;
			if(!ChooseColorW(&cci))return 0;
			colors[0] = GetRValue(cci.rgbResult);
			colors[1] = GetGValue(cci.rgbResult);
			colors[2] = GetBValue(cci.rgbResult);
			ofstream wf(datapath, ios::out | ios::binary | ios::trunc);
			if (!wf) {
				MessageBoxFormatW(MB_OK | MB_ICONERROR,
					L"",
					hDlg,
					GetLanguageTablePtr()->operator[]("lng.tip.fail_to_write").c_str(),
					datapath);
				return 0;
			}
			wf.write((char*)colors, 3);
			wf.close();
			InvalidateRect(hDlg, nullptr, TRUE);
		}else if (LOWORD(wParam) == IDC_MDC) {
			unsigned char colors[3] = { 0, 0, 0};
			wchar_t datapath[512] = { 0 };
			SHGetSpecialFolderPathW(nullptr, datapath, CSIDL_APPDATA, TRUE);
			wsprintfW(datapath, L"%s%s", datapath, L"\\Jiusay\\mbg_bgc_1.dat");
			CHOOSECOLORW cci = { 0 };

			ifstream rf(datapath);
			rf.read((char*)colors, 3);
			rf.close();
			cci.rgbResult = RGB(colors[0], colors[1], colors[2]);

			cci.lStructSize = sizeof(CHOOSECOLORW);
			cci.hwndOwner = hDlg;
			cci.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
			COLORREF arr[16] = { 0 };
			cci.lpCustColors = arr;
			if (!ChooseColorW(&cci))return 0;
			HDC dc = GetDC(GetDlgItem(hDlg, LOWORD(wParam)));
			SetBkColor(dc, cci.rgbResult);
			ReleaseDC(GetDlgItem(hDlg, LOWORD(wParam)), dc);
			colors[0] = GetRValue(cci.rgbResult);
			colors[1] = GetGValue(cci.rgbResult);
			colors[2] = GetBValue(cci.rgbResult);
			ofstream wf(datapath, ios::out | ios::binary | ios::trunc);
			if (!wf) {
				MessageBoxFormatW(MB_OK | MB_ICONERROR,
					L"",
					hDlg,
					GetLanguageTablePtr()->operator[]("lng.tip.fail_to_write").c_str(),
					datapath);
				return 0;
			}
			wf.write((char*)colors, 3);
			wf.close();
			InvalidateRect(hDlg, nullptr, TRUE);
		}else if (LOWORD(wParam) == IDC_MDL) {
			unsigned char colors[3] = { 0, 0, 0};
			wchar_t datapath[512] = { 0 };
			SHGetSpecialFolderPathW(nullptr, datapath, CSIDL_APPDATA, TRUE);
			wsprintfW(datapath, L"%s%s", datapath, L"\\Jiusay\\mbg_bgc_2.dat");
			CHOOSECOLORW cci = { 0 };

			ifstream rf(datapath);
			rf.read((char*)colors, 3);
			rf.close();
			cci.rgbResult = RGB(colors[0], colors[1], colors[2]);

			cci.lStructSize = sizeof(CHOOSECOLORW);
			cci.hwndOwner = hDlg;
			cci.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
			COLORREF arr[16] = { 0 };
			cci.lpCustColors = arr;
			if (!ChooseColorW(&cci))return 0;
			colors[0] = GetRValue(cci.rgbResult);
			colors[1] = GetGValue(cci.rgbResult);
			colors[2] = GetBValue(cci.rgbResult);
			ofstream wf(datapath, ios::out | ios::binary | ios::trunc);
			if (!wf) {
				MessageBoxFormatW(MB_OK | MB_ICONERROR,
					L"",
					hDlg,
					GetLanguageTablePtr()->operator[]("lng.tip.fail_to_write").c_str(),
					datapath);
				return 0;
			}
			wf.write((char*)colors, 3);
			wf.close();
			InvalidateRect(hDlg, nullptr, TRUE);
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		int ctrlid = GetDlgCtrlID((HWND)lParam);
		if (ctrlid != IDC_KDC && ctrlid != IDC_MDC && ctrlid != IDC_MDL)
			return (INT_PTR)GetStockObject(NULL_BRUSH);
		wchar_t datapath[512] = { 0 };
		unsigned char colors[3] = { 0 };
		SHGetSpecialFolderPathW(nullptr, datapath, CSIDL_APPDATA, TRUE);
		switch (ctrlid)
		{
		case IDC_KDC:
			wsprintfW(datapath, L"%s%s", datapath, L"\\Jiusay\\kbg_bgc.dat");
			break;
		case IDC_MDC:
			wsprintfW(datapath, L"%s%s", datapath, L"\\Jiusay\\mbg_bgc_1.dat");
			break;
		case IDC_MDL:
			wsprintfW(datapath, L"%s%s", datapath, L"\\Jiusay\\mbg_bgc_2.dat");
			break;
		}
		HBRUSH hb = nullptr;
		ifstream rf(datapath);
		if (!rf){
			return (INT_PTR)(INT_PTR)GetStockObject(NULL_BRUSH);
		}
		rf.read((char*)colors, 3);
		rf.close();
		hb = CreateSolidBrush(RGB(colors[0], colors[1], colors[2]));
		bgcs.push_back(hb);
		SetBkColor((HDC)wParam, RGB(colors[0], colors[1], colors[2]));
		return (INT_PTR)hb;
	}
		break;
	default:
		break;
	}
	return 0;
}
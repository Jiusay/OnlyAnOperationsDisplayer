#include <map>
#include <string>
#include <fstream>
#include <codecvt>
#include <locale>
using namespace std;

void CreateDefaultLanguageTable(map<string, wstring>& lt) {
	lt.insert({ "lng.tip.fail_to_register",L"注册窗口类失败\n请尝试重启程序" });
	lt.insert({ "lng.tip.fail_to_create_wnd",L"创建窗口失败\n请尝试重启程序" });
	lt.insert({ "lng.txt.topmost",L"窗口置顶" });
	lt.insert({ "lng.txt.show_keys",L"按键显示" });
	lt.insert({ "lng.txt.lock_sk_wnd",L"锁定按键显示悬浮窗" });
	lt.insert({ "lng.tip.fail_to_open",L"无法开启功能\n%s" });
	lt.insert({ "lng.txt.floatingw_size",L"悬浮窗大小:" });
	lt.insert({ "lng.tip.lng_changed",L"您更改了语言设置，\n但这需要重新启动程序才可以生效\n是否立即重新启动程序？" });
	lt.insert({ "lng.tip.fail_to_restart",L"程序无法自动重启，请您手动重启" });
	lt.insert({ "lng.txt.show_mouse",L"显示鼠标位置" });
	lt.insert({ "lng.txt.show_mouseop",L"显示鼠标操作" });
	lt.insert({ "lng.txt.elngf",L"外部语言文件..." });
	lt.insert({ "lng.txt.appearance",L"外观..." });
	lt.insert({ "lng.txt.color",L"颜色..." });
	lt.insert({ "lng.txt.kbddc",L"按键显示悬浮窗" });
	lt.insert({ "lng.txt.mousedc_c",L"鼠标显示悬浮窗" });
	lt.insert({ "lng.txt.mousedc_l",L"鼠标按下" });
	lt.insert({ "lng.txt.ok",L"确定" });
	lt.insert({ "lng.txt.cancel",L"取消" });
	lt.insert({ "lng.tip.fail_to_write",L"无法写入此文件\n%s" });
	lt.insert({ "lng.txt.req_reopen",L"重启对应功能生效" });
}

void CreateDefaultLanguageTable2(map<string, wstring>& lt) {
	lt.insert({ "lng.tip.fail_to_register",L"Fail to register the class name\nPlease try to restart the program" });
	lt.insert({ "lng.tip.fail_to_create_wnd",L"Fail to create the window\nPlease try to restart the program" });
	lt.insert({ "lng.txt.topmost",L"Keep the window in front mostly" });
	lt.insert({ "lng.txt.show_keys",L"Display keys" });
	lt.insert({ "lng.txt.lock_sk_wnd",L"Lock the floating window for keys displaying" });
	lt.insert({ "lng.tip.fail_to_open",L"Cannot open this option\n%s" });
	lt.insert({ "lng.txt.floatingw_size",L"Size of floating window:" });
	lt.insert({ "lng.tip.lng_changed",L"You changed the language settings,\nbut it requires a restart of the program for it to take effect\nDo you want to restart the program immediately?" });
	lt.insert({ "lng.tip.fail_to_restart",L"The program cannot be restarted automatically,\nso please restart it manually" });
	lt.insert({ "lng.txt.show_mouse",L"Show the position of mouse" });
	lt.insert({ "lng.txt.show_mouseop",L"Show the operations of mouse" });
	lt.insert({ "lng.txt.elngf",L"External language files..." });
	lt.insert({ "lng.txt.appearance",L"Appearance..." });
	lt.insert({ "lng.txt.color",L"Color settings..." });
	lt.insert({ "lng.txt.kbddc",L"Keys displaying" });
	lt.insert({ "lng.txt.mousedc_c",L"Mouse displaying" });
	lt.insert({ "lng.txt.mousedc_l",L"Mouse Clicked" });
	lt.insert({ "lng.txt.ok",L"OK" });
	lt.insert({ "lng.txt.cancel",L"Cancel" });
	lt.insert({ "lng.tip.fail_to_write",L"Cannot write this file\n%s" });
	lt.insert({ "lng.txt.req_reopen",L"The changes will take effect when you restart the functions" });
}

bool LoadLanguageFile(wchar_t* path, map<string, wstring>& lt) {
	wstring buffer, lid, ltxt;
	wifstream lfs(path);
	CreateDefaultLanguageTable(lt);
	if (!lfs)return false;
	wstring_convert<codecvt_utf8<wchar_t>> w2a;
	while (getline(lfs, buffer)) {
		if (buffer.find(L'=') == wstring::npos)continue;
		lid = buffer.substr(0, buffer.find(L'='));
		ltxt = buffer.substr(buffer.find(L'=') + 1);
		lt[w2a.to_bytes(lid)] = ltxt;
	}
	lfs.close();
	return true;
}
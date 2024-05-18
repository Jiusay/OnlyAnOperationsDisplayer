#include <map>
#include <string>
using namespace std;
void CreateDefaultLanguageTable(map<string, wstring>& lt) {
	lt.insert({ "lng.tip.fail_to_register",L"注册窗口类失败\n请尝试重启程序" });
	lt.insert({ "lng.tip.fail_to_create_wnd",L"创建窗口失败\n请尝试重启程序" });
	lt.insert({ "lng.txt.topmost",L"窗口置顶" });
	lt.insert({ "lng.txt.minimze_in_using_other_wnd",L"操作其他窗口时最小化" });
	lt.insert({ "lng.txt.show_keys",L"按键显示" });
	lt.insert({ "lng.txt.sk_without_entrying",L"输入时关闭按键显示" });
	lt.insert({ "lng.tip.fail_to_open",L"无法开启功能\n%s" });
	lt.insert({ "lng.txt.floatingw_size",L"悬浮窗大小:" });
	lt.insert({ "lng.tip.lng_changed",L"您更改了语言设置，\n但这需要重新启动程序才可以生效\n是否立即重新启动程序？" });
	lt.insert({ "lng.tip.fail_to_restart",L"程序无法自动重启，请您手动重启" });
}

void CreateDefaultLanguageTable2(map<string, wstring>& lt) {
	lt.insert({ "lng.tip.fail_to_register",L"Fail to register the class name\nPlease try to restart the program" });
	lt.insert({ "lng.tip.fail_to_create_wnd",L"Fail to create the window\nPlease try to restart the program" });
	lt.insert({ "lng.txt.topmost",L"Keep the window in front mostly" });
	lt.insert({ "lng.txt.minimze_in_using_other_wnd",L"Minimize when using other windows" });
	lt.insert({ "lng.txt.show_keys",L"Display keys" });
	lt.insert({ "lng.txt.sk_without_entrying",L"Pause displaying keys while inputting" });
	lt.insert({ "lng.tip.fail_to_open",L"Cannot open this option\n%s" });
	lt.insert({ "lng.txt.floatingw_size",L"Size of floating window:" });
	lt.insert({ "lng.tip.lng_changed",L"You changed the language settings,\nbut it requires a restart of the program for it to take effect\nDo you want to restart the program immediately?" });
	lt.insert({ "lng.tip.fail_to_restart",L"The program cannot be restarted automatically,\nso please restart it manually" });
}
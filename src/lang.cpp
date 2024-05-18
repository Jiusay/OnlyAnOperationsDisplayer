#include <map>
#include <string>
using namespace std;
void CreateDefaultLanguageTable(map<string, wstring>& lt) {
	lt.insert({ "lng.tip.fail_to_register",L"ע�ᴰ����ʧ��\n�볢����������" });
	lt.insert({ "lng.tip.fail_to_create_wnd",L"��������ʧ��\n�볢����������" });
	lt.insert({ "lng.txt.topmost",L"�����ö�" });
	lt.insert({ "lng.txt.minimze_in_using_other_wnd",L"������������ʱ��С��" });
	lt.insert({ "lng.txt.show_keys",L"������ʾ" });
	lt.insert({ "lng.txt.sk_without_entrying",L"����ʱ�رհ�����ʾ" });
	lt.insert({ "lng.tip.fail_to_open",L"�޷���������\n%s" });
	lt.insert({ "lng.txt.floatingw_size",L"��������С:" });
	lt.insert({ "lng.tip.lng_changed",L"���������������ã�\n������Ҫ������������ſ�����Ч\n�Ƿ�����������������" });
	lt.insert({ "lng.tip.fail_to_restart",L"�����޷��Զ������������ֶ�����" });
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
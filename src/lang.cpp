#include <map>
#include <string>
#include <fstream>
#include <codecvt>
#include <locale>
using namespace std;

void CreateDefaultLanguageTable(map<string, wstring>& lt) {
	lt.insert({ "lng.tip.fail_to_register",L"ע�ᴰ����ʧ��\n�볢����������" });
	lt.insert({ "lng.tip.fail_to_create_wnd",L"��������ʧ��\n�볢����������" });
	lt.insert({ "lng.txt.topmost",L"�����ö�" });
	lt.insert({ "lng.txt.show_keys",L"������ʾ" });
	lt.insert({ "lng.txt.lock_sk_wnd",L"����������ʾ������" });
	lt.insert({ "lng.tip.fail_to_open",L"�޷���������\n%s" });
	lt.insert({ "lng.txt.floatingw_size",L"��������С:" });
	lt.insert({ "lng.tip.lng_changed",L"���������������ã�\n������Ҫ������������ſ�����Ч\n�Ƿ�����������������" });
	lt.insert({ "lng.tip.fail_to_restart",L"�����޷��Զ������������ֶ�����" });
	lt.insert({ "lng.txt.show_mouse",L"��ʾ���λ��" });
	lt.insert({ "lng.txt.show_mouseop",L"��ʾ������" });
	lt.insert({ "lng.txt.elngf",L"�ⲿ�����ļ�..." });
	lt.insert({ "lng.txt.appearance",L"���..." });
	lt.insert({ "lng.txt.color",L"��ɫ..." });
	lt.insert({ "lng.txt.kbddc",L"������ʾ������" });
	lt.insert({ "lng.txt.mousedc_c",L"�����ʾ������" });
	lt.insert({ "lng.txt.mousedc_l",L"��갴��" });
	lt.insert({ "lng.txt.ok",L"ȷ��" });
	lt.insert({ "lng.txt.cancel",L"ȡ��" });
	lt.insert({ "lng.tip.fail_to_write",L"�޷�д����ļ�\n%s" });
	lt.insert({ "lng.txt.req_reopen",L"������Ӧ������Ч" });
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
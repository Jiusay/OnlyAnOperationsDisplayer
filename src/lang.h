#pragma once

void CreateDefaultLanguageTable(map<string, wstring>& lt);
void CreateDefaultLanguageTable2(map<string, wstring>& lt);
bool LoadLanguageFile(wchar_t* path, map<string, wstring>& lt);
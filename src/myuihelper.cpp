#include <Windows.h>
template <class T, class...Args>
UINT MessageBoxFormatW(UINT flags,
	const wchar_t* const title,
	HWND parent,
	T first,
	Args...texts) {
	wchar_t buffer[1024] = { 0 };
	wsprintfW(buffer, first, texts...);
	return MessageBoxW(parent, buffer, title, flags);
}
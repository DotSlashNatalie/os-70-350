//C++ - using vectors as C arrays
#include <vector>
#include <iostream>
#include <Windows.h>
#include <string>

int main()
{
	std::vector<wchar_t> wstr;
	std::string x = "normal string";
	wstr.resize(x.size() + 1);
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, &wstr[0], x.size() + 1, x.c_str(), _TRUNCATE);
	std::wcout << &wstr[0] << std::endl;
}
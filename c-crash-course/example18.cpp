//C++ - using vectors as C arrays
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
	std::vector<wchar_t> wstr;
	std::string x = "normal string";
	std::wstring z = std::wstring(x.begin(), x.end());
	std::wcout << z.c_str() << std::endl;
	std::wcout << &z[0] << std::endl;
}
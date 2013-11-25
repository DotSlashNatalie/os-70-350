#include <Windows.h>

void WriteStr(const char * str)
{
	HANDLE stdout2 = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD byteswritten;
	int length = 0;
	const char * cpyptr = str;
	while(*cpyptr != 0)
	{
		cpyptr++;
		length += 1;
	}
	WriteFile(stdout2, str, sizeof(str), &byteswritten, NULL);
}

int main(int argc, char * args[])
{
	WriteStr("abc");
	if (argc != 2)
	{
		WriteStr("Please enter two parameters - cp src dst");
	}
	
	HANDLE hsrc = CreateFileA(args[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		WriteStr("Could not find file!");
		return 0;
	}


}
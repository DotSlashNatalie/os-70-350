#include <Windows.h>
#include <string>
#include <vector>


void WriteStr(const char * str)
{
	// A simple wrapper to output text using WriteFile
	HANDLE stdout2 = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD byteswritten;
	int length = 0;
	const char * cpyptr = str;
	while(*cpyptr++) // This doesn't work the way you would expect it
		length++;
	WriteFile(stdout2, str, length, &byteswritten, NULL);
}

class FileWrapper
{
private:
	HANDLE _handle;

public:
	FileWrapper(const char * file, DWORD access, DWORD creation) { this->_handle = CreateFileA(file, access, 0, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL); }
	~FileWrapper() { CloseHandle(this->_handle); } // http://msdn.microsoft.com/en-us/library/windows/desktop/ms724211(v=vs.85).aspx
	HANDLE getHandle() { return this->_handle; }
};

int main(int argc, char * args[])
{
	// Parameter checking
	if (argc != 3)
	{
		WriteStr("Please enter two parameters - cp src dst");
		return 0;
	}
	
	// Open the source
	// A little RAII
	{
	FileWrapper src(args[1], GENERIC_READ, OPEN_EXISTING);
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		WriteStr("Could not find file!");
		return 0;
	}

	// Open destination file
	FileWrapper dst(args[2], GENERIC_WRITE, CREATE_ALWAYS);
	
	DWORD numberofbytesread;
	DWORD numberofbyteswritten;
	char buffer[20];

	// Stream the file instead of reading it into memory
	while(true)
	{
		// The buffer parameter is a void pointer which means it can take anything - in this case we just use a char array
		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa365467(v=vs.85).aspx
		ReadFile(src.getHandle(), buffer, 20, &numberofbytesread, NULL); // http://stackoverflow.com/questions/12655120/readfile-function-from-win32-api
		if (numberofbytesread == 0)
			break;
		WriteFile(dst.getHandle(), buffer, numberofbytesread, &numberofbyteswritten, NULL);
	}
	}
	
	std::vector<wchar_t> wstr;
	std::string x = args[1];
	wstr.resize(x.size() + 1);
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, &wstr[0], x.size() + 1, x.c_str(), _TRUNCATE);
	return 0;
}
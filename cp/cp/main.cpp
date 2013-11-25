#include <Windows.h>

void WriteStr(const char * str)
{
	// A simple wrapper to output text using WriteFile
	HANDLE stdout2 = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD byteswritten;
	int length = 0;
	const char * cpyptr = str;
	while(*cpyptr++)
		length++;
	WriteFile(stdout2, str, length, &byteswritten, NULL);
}

class FileWrapper
{
private:
	HANDLE _handle;

public:
	FileWrapper(const char * file, DWORD access, DWORD creation) { this->_handle = CreateFileA(file, access, 0, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL); }
	~FileWrapper() { CloseHandle(this->_handle); }
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
		ReadFile(src.getHandle(), buffer, 20, &numberofbytesread, NULL);
		if (numberofbytesread == 0)
			break;
		WriteFile(dst.getHandle(), buffer, numberofbytesread, &numberofbyteswritten, NULL);
	}
	
	return 0;
}
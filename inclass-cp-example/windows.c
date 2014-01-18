#include <stdio.h>
#include <Windows.h>
#define false 0
#define true 1

// cp2 file1 file2
int main(int argc, char * args[])
{
	HANDLE infile;
	HANDLE outfile;
	DWORD numberofbytesread;
	DWORD numberofbyteswritten;
	char buffer[20];
	
	infile = CreateFileA(args[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		printf("Could not find file!");
		return 0;
	}
	
	outfile = CreateFileA(args[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	while(true)
	{
		ReadFile(infile, buffer, 20, &numberofbytesread, NULL);
		if (numberofbytesread == 0)
			break;
		WriteFile(outfile, buffer, numberofbytesread, &numberofbyteswritten, NULL);
	}
	
	CloseHandle(infile);
	CloseHandle(outfile);
	
	return 0;
}
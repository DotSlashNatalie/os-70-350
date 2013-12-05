#ifdef __linux__
#include <unistd.h> // read, write
#include <errno.h> // ENOENT
#include <fcntl.h> // O_RDONLY and O_WRONLY
#else
// assume any other platform is Windows
#include <Windows.h>
#endif

class FileWrapper
{
#ifdef __linux__
private:
// ... Linux FileWrapper code goes here
#else
private:
// ... Windows FileWrapper here
#endif
}

void cp(const char * src, const char * dest)
{
    char buffer[20];
#ifdef __linux__
	// Linux code goes here
#else
	// Windows code goes here
#endif
}

int main()
{
	// Don't ask user for file
	cp("test.txt", "test2.txt");
}
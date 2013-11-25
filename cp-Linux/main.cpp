#include <unistd.h> // read, write
#include <errno.h> // ENOENT
#include <fcntl.h> // O_RDONLY and O_WRONLY

void WriteStr(const char * str)
{
	// A simple wrapper to output text using Write
	int length = 0;
	const char * cpyptr = str;
	while(*cpyptr++) // This doesn't work the way you would expect it
		length++;
    write(1, str, length);
}

class FileWrapper
{
private:
	int _handle;

public:
	FileWrapper(const char * file, int flags, mode_t mode = 0700) { this->_handle = open(file, flags, mode); }
	~FileWrapper() { close(this->_handle); }
	int getHandle() { return this->_handle; }
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
	FileWrapper src(args[1], O_RDONLY);
    if (src.getHandle() == ENOENT)
    {
        WriteStr("Could not find file!");
		return 0;
    }

    FileWrapper dst(args[2], O_WRONLY | O_CREAT);

    int numofbytesread;
    char buffer[20];

    // Stream the file instead of reading it into memory
    // The buffer parameter is a void pointer which means it can take anything - in this case we just use a char array
	while ((numofbytesread = read(src.getHandle(), buffer, 20)))
        write(dst.getHandle(), buffer, numofbytesread);

    return 0;
}

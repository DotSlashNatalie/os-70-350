#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

// cp2 file1 file2
int main(int argc, char * args[])
{
	int infile, outfile;
	int numofbytesread;
	char buffer[20];

	infile = open(args[1], O_RDONLY, 0700);
	if (infile == ENOENT)
	{   
			printf("Could not find file!");
			return 0;    
	}   

	outfile = open(args[2], O_WRONLY | O_CREAT, 0700);

	while((numofbytesread = read(infile, buffer, 20)))
			write(outfile, buffer, numofbytesread);

	close(infile);
	close(outfile);
	
	return 0;
}	
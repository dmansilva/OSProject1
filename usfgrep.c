/* usfgrep - a simple version of grep that can search one or more files */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
	printf("Insufficient arguments.\n");
	printf("usage: usfgrep <string> <file1> [<file2> ...]\n");
	printf("\n");
	exit(-1);
    }
    
    printf("hi!\n");
    
    return 0;
}

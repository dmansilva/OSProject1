/* usfgrep - a simple version of grep that can search one or more files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int fd;


void file_contents(int fd, int stringCount, char *argString, char *argFile) {

	
	int bytes_read;
	char each_Line[512];
	char t;
	int fileCount = 0;
	int lineCounter = 0;
	int i = 0;
	
	// check to see if file can be opened
    if (fd < 0) {														
        printf("Cannot open file");
        exit(1);
    }

    while ((bytes_read = read(fd , &t, 1)) > 0) {						// goes through the file character at a time, checks if char read is > 0

    	fileCount++;													// counter for every single byte
    	
    	if (t == '\n' || t == '\0') {

    		if (fileCount > 511) {											// a check to see if the file is bigger than 511
    			printf("The line is too long");
    			exit(-1);												// break out if it is bigger
    		}

    		fileCount = 0;
	    	lineCounter++;
	    	int comp;
	    	int z;
	    	int line_length;
	    	line_length = strlen(each_Line);
	    	each_Line[line_length] = '\0';

	    	for (z = 0; z < strlen(each_Line); z++) {							// iterate through the bytes in the line read

	    		comp = strncmp(each_Line + z, argString, stringCount);		// strn compare the line read in with argumentString, comparing by length of argString
	    		if (comp == 0) {
	    			printf("%s [%d]:%s\n", argFile, lineCounter, each_Line);		
	    			break;
	    		}
	    	}
	    	               			
	    	memset(each_Line, '\0', 512);				// memset sets all bytes in my char array to null character
	    	
	    	i = 0;													// resetting i to 0 for index of eachLine char array
	    	
	    }
	    else {															// else means that the next character read == a newline character
	    	each_Line[i++] = t;											// adding the character byte to my char array for each_Line
	    }
    }
}

int main(int argc, char *argv[])  {

    if (argc < 3) {
		printf("Insufficient arguments.\n");
		printf("usage: usfgrep <string> <file1> [<file2> ...]\n");
		printf("\n");
		exit(-1);
    }

    int length = strlen(argv[1]);    					// need the count of the string from the command line argument

    char *argString;
    argString = malloc(length);
    argString = argv[1];         						// gets the string from the command line argument

    char *argFile;
 
    int i;
    for (i = 2; i < argc; i++) {
    	fd = open(argv[i], O_RDONLY);							// open the file and save it to an int file descriptor
    	argFile = malloc(strlen(argv[i]));						// malloc space for the file name
    	argFile = argv[i];										// save file name to the variable we malloced for
    	file_contents(fd, length, argString, argFile);			// call file_contents functions to grep the lines we want
    	close(fd);												// close the file before the next iteration
    }
    
    return 0;
}





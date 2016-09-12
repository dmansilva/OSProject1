/* usfgrep - a simple version of grep that can search one or more files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int fd;


void file_contents(int fd, int stringCount, char *argString) {

	
	int bytes_read;
	char each_Line[511];
	char t;
	int fileCount = 0;
	//char = 0;
	int i = 0;
	int currIndex = 0;
	int printLine = 0;
	int argStringLength = strlen(argString);
	
	
    if (fd < 0) {
        printf("Cannot open file");
        exit(1);
    }

    while ((bytes_read = read(fd , &t, 1)) > 0) {						// goes through the file character at a time, checks if char read is > 0
    	fileCount++;													// counter for every single byte
    	if (fileCount > 511) {											// a check to see if the file is bigger than 511
    		printf("The line is too long");
    		exit(-1);												// break out if it is bigger
    	}
    	if (t != '\n') {
	    	each_Line[i++] = t;											// adding the character byte to my char array for each_Line
	    	//printf("%c\n", t);
	    	//printf("%s \n", each_Line);
	    	//if (argString[currIndex] == t) {				// check to see if the character read in equals the character at the currentIndex of argString
	    	//	currIndex++;											// indexing currentIndex of argString
	    	//	if (currIndex == stringCount) {							// checking currIndex size vs StringCount to see if complete word is matched
	    	//		printLine = 1;										// indicator to print the Line or not
	    	//	}
	    	//}
	    	//else {
	    	//	currIndex = 0;											// resets the currentIndex everytime a character is not matched
	    	//}
	    	//printLine = 1;
	    	
	    }
	    else {															// else means that the next character read == a newline character
	    	//if (printLine == 1) {
	    	//int lineCount = strlen(each_Line);
	    	//lineCount++;
	    	//each_Line[lineCount] = '\0';					// need to add null terminating character to a char array if i want to print out as string
	    	int comp;
	    	for (int z = 0; z < strlen(each_Line); z++) {

	    		comp = strncmp(each_Line + z, argString, argStringLength);
	    		if (comp == 0) {
	    			printf("%s\n", each_Line);
	    			break;
	    		}

	    	}
	    	//printf("%s \n", each_Line);                			// printing out the line from each_Line char array
	    	//printLine = 0;											// reseting the printLine to 0
	    	memset(each_Line, '\0', strlen(each_Line));				// function that will set the each_Line char array to empty essentially
	    	i = 0;													// resetting i to 0 for index of eachLine char array
	    	//}
	    }

    }



}

// char reset_LineChar(char* array) {
	

// 	for (int i = 0; i < strlen(array); i++) {
// 		array[i] = '\0';
// 	}

// 	return array;
// }

int main(int argc, char *argv[])
{
    if (argc < 3) {
		printf("Insufficient arguments.\n");
		printf("usage: usfgrep <string> <file1> [<file2> ...]\n");
		printf("\n");
		exit(-1);
    }

    int length = strlen(argv[1]);    // need the count of the string from the command line argument

    char *argString;
    argString = malloc(length);
    argString = argv[1];         // gets the string from the command line argument
 

    for (int i = 2; i < argc; i++) {

    	// call my read file contents line by line function
    	fd = open(argv[i], O_RDONLY);
    	file_contents(fd, length, argString);
    	close(fd);
    }
    
    printf("hi!\n");
    
    return 0;
}
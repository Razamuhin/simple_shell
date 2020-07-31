/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


// create - creates a new file
// filename - the name of the file to be created
int create(char **arguments){
	FILE *newfile;
	newfile = fopen(arguments[1],"w");
	//check for leading whitespace
	fclose(newfile);
	return 0;
}

// update - appends lines of text to a file
// filename - the name of the target file
// numlines - number of lines to add
// text - text in each line
int update(char **arguments){
	int numlines;
	//FILE *workfile;
	numlines = atoi(arguments[2]);
	printf("Number of lines: %d\n", numlines);
	/*while(arguments[n]!=NULL){
		printf("%s",arguments[n]);
		n++;
		// while not null or quote, use a simple if statement
	}*/
	printf("%s\n",arguments[3]);
	//printf("%s\n",arguments[3]);
	//for(n=3;n<numlines;n++){}
	//workfile = fopen(arguments[1],"a");
	//for(n=0;n<numlines;n++){
	//	fprintf( workfile, arguments[3] );
	//	fflush(workfile);
	//}
	//fclose(workfile);
	return 0;
}

// list - displays contents of a file
//		Parameters:
// 			arguments - the name of the target file
//		Maximum file size: 1MB
int list(char **arguments){
	FILE *readfile;
	char filebuffer[10000];
	readfile = fopen(arguments[1],"r");
	//if fopen(...) == NULL -> return error
	fclose(readfile);
	snprintf(filebuffer,9999,"%s",arguments[1]);
	execl("/bin/cat","cat",filebuffer,NULL);
	return 0;
}

// dir - uses the Linux ls system builtin to list files in the current directory
int dir(){
	execl("/bin/ls","ls",NULL);
	return 0;
}

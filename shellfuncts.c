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
int create(char **filename){
	FILE *newfile;
	newfile = fopen(filename[1],"w");
	fclose(newfile);
}

// update - appends lines of text to a file
// filename - the name of the target file
// numlines - number of lines to add
// text - text in each line
int update(char **filename){
	int numlines;
	int n = 0;
	//FILE *workfile;
	numlines = atoi(filename[2]);
	while(filename[n]!=NULL){
		printf("%s",filename[n]);
		n++;
	}
	//printf("%s\n",filename[3]);
	//for(n=3;n<numlines;n++){}
	//workfile = fopen(filename[1],"a");
	//for(n=0;n<numlines;n++){
	//	fprintf( workfile, filename[3] );
	//	fflush(workfile);
	//}
	//fclose(workfile);
	return 0;
}

// list - displays contents of a file
//		Parameters:
// 			filename - the name of the target file
//		Maximum file size: 1MB
int list(char **filename){
	FILE *readfile;
	char *filebuffer = malloc(1048576 * sizeof(char));
	readfile = fopen(filename[1],"r");
	snprintf(filebuffer,(1048576 * sizeof(char)) - 1,"cat %s",filename[1]);
	system(filebuffer);
	free(filebuffer);
	fclose(readfile);
	return 0;
}

// dir - uses the Linux ls system builtin to list files in the current directory
int dir(){
	execl("/bin/ls","ls",NULL);
	return 0;
}

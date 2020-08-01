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
	if(fopen(arguments[1],"r")!=NULL){
		fprintf(stderr,"[ERROR]: File '%s' already exists!\n",arguments[1]);
	} else {
		FILE *newfile;
		newfile = fopen(arguments[1],"w");
		// Check for leading whitespace
		fclose(newfile);
	}
	exit(0);
}

// update - appends lines of text to a file
int update(char **arguments){
	int numlines, n;
	// Check whether file exists
	if(fopen(arguments[1],"r")==NULL){
		fprintf(stderr,"[ERROR]: File '%s' not found!\n",arguments[1]);
	} else {
		FILE *workfile;
		numlines = atoi(arguments[2]);
		workfile = fopen(arguments[1],"a");
		for(n=0;n<numlines;n++){
			fprintf( workfile, "%s\n",arguments[3] );
			fflush(workfile);
		}
		sleep(strlen(arguments[3])/5);
		fclose(workfile);
		printf("File update complete for PID: %d\n",getpid());
	}
	exit(0);
}

// list - displays contents of a file
int list(char **arguments){
	char filebuffer[100];
	// Check whether file exists
	if(fopen(arguments[1],"r")==NULL){
		fprintf(stderr, "File '%s' not found!\n",arguments[1]);
	} else {
		snprintf(filebuffer,99,"%s",arguments[1]);
		execl("/bin/cat","cat",filebuffer,NULL);
	}
	exit(0);
}

// dir - uses the Linux ls binary to list files in the current directory
int dir(){
	execl("/bin/ls","ls",NULL);
	exit(0);
}

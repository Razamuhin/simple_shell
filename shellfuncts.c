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
//#include "shellfuncts.h"

// Set max length of command
#define MAX_LENGTH 100

// Declare array to hold command line input
char *args[MAX_LENGTH];

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
	int n,numlines;
	//FILE *workfile;
	numlines = atoi(filename[2]);
	printf("%s\n",filename[3]);
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
	fclose(readfile);
	return 0;
}

// dir - uses the Linux ls system builtin to list files in the current directory
int dir(){
	execl("/bin/ls","ls",NULL);
	return 0;
}

// Create arrays of commands and their addresses, to use when calling functions
char *commands[] = { "create", "update", "list", "dir" };
int (*cmd[]) (char **) = { &create, &update, &list, &dir };

// parse_input - takes user input and breaks it into a matrix of arguments
// *input - pointer to user input
int parse_input(char *input){
	int bgcheck = 0;
	// Replace newline at end of command with null character

	input[strlen(input)-1] = '\0';
	// test print
	// printf("%s\n",input);

	// split user input into matrix of arguments
	char *arg = strtok(input," ");
	printf("%s",input);
	int i = 0;
	while(arg != NULL){
		args[i] = arg;
		arg = strtok(NULL," ");
		i++;
	}
	args[i] = NULL;
	// check whether last argument is '&', set bgcheck flag accordingly
	if(strcmp(args[i-1],"&")==0){ bgcheck = 1; }
	return bgcheck;
}

// execute shell command
// reference: https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
int exec_cmd(int bgcheck){
	int i = 0;
	int err_chk = 1;
	int status;
	pid_t pid;
	pid = fork();
	if (pid==0) {
		if(bgcheck=1){
			setpgid(0,0);
		}
		for(i=0;i<4;i++){
			if (strcmp(args[0], commands[i]) == 0 ) {
				printf("Starting child process %s with pid %d\n",args[0],getpid());
				err_chk = 0;
				return (*cmd[i])(args);
				exit(EXIT_SUCCESS);
			}
		}
		if (err_chk == 1) {
			fprintf(stderr,"Command not recognized!\n");
		}
	} else {
		//hanging! fix this
		wait(&status);
	}
	return 0;
}

int main(void){
	// References:
	// https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf
	// https://brennan.io/2015/01/16/write-a-shell-in-c/
	// Allocate memory for user arguments, and exit gracefully if no memory is available.
	char input[MAX_LENGTH];
	int bgcheck;
	//char *input = malloc(MAX_LENGTH * sizeof(char*));

	if(input == NULL){
		fprintf(stderr,"Out of memory - please download additional RAM\n");
		return 1;
	}

	int cont = 1;

	// use getpid() to get and print the process id for this command loop
	printf("Shell pid is %d\n",getpid());
	// prompt user for next command

	while(cont == 1){
		// shell prompt
		printf("wash> ");
		fgets(input, MAX_LENGTH, stdin);
		printf("%s\n",input);
		//fflush(stdout);
		// parse command
		bgcheck = parse_input(input);
		if (args[0] == NULL) {												// if no text recieved, print error
			fprintf(stderr,"No command received\n");
		} else if (strcmp(args[0], "halt") == 0) {		// if command is halt, exit shell
			cont = 0;
		} else {
			// fork and execute new process
			exec_cmd(bgcheck);
		}

		// fork() child process to execute command

		// print process id of the child process
		// if command is in the foreground, wait for it to complete
		//end loop

	}

	return 0;
}

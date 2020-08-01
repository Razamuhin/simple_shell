/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489
 *
 *************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "shellfuncts.h"

// Set max length of command
#define MAX_LENGTH 1000

// Declare array to hold command line input
char *args[MAX_LENGTH];
char buffer[100];

// parse_input - takes user input and breaks it into a matrix of arguments
// Reference:
// https://brennan.io/2015/01/16/write-a-shell-in-c/ (see main)
bool parse_input(char *input){
	bool bgcheck = false;
	int i = 0;
	input[strlen(input)-1] = '\0';
	args[0] = strtok(input," ");
	while(args[i] != NULL){
		if(*args[i]=='"'){
			args[i]++;
			char *tmp = strtok(NULL,"\"");
			snprintf(buffer, 100, "%s %s",args[i], tmp);
			//strcat(args[i],tmp);
			args[i] = buffer;
		}
		args[i+1] = strtok(NULL," ");
		++i;
	}
	if(args[0] != NULL && strcmp(args[i-1],"&")==0){ bgcheck = true; }
	return bgcheck;
}

// execute shell command
// Used this reference:
// https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
int exec_cmd(bool bgcheck){
	int i = 0, status;
	bool err_chk = true;
	pid_t pid;
	pid = fork();
	if (pid==0) {
		// Compare first argument with list of available functions
		while(commands[i]!=NULL){
			if (strcmp(args[0], commands[i]) == 0 ) {
				printf("Starting child process %s with pid %d\n",args[0],getpid());
				err_chk = false;
				return (*cmd[i])(args);									// Execute function with arguments
			}
			i++;
		}
		exit(0);
		if (err_chk) {
			fprintf(stderr,"Command not recognized!\n");
			exit(0);
		}
	} else {
		if(!bgcheck){ waitpid(pid,&status,0); }
	}
	return 0;
}

int main(void){
	// References:
	// https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf - for fgets examples
	// https://brennan.io/2015/01/16/write-a-shell-in-c/ - used this article's model for storing command line arguments and calling builtin shell functions
	char input[MAX_LENGTH];
	bool bgcheck = false, cont = true;							// While loop exit condition
	printf("Shell pid is %d\n",getpid());						// Print the process id for this command loop

	// prompt user for next command
	while(cont){
		// shell prompt
		printf("msh > ");
		fflush(stdout);
		fgets(input, MAX_LENGTH, stdin);

		// parse command
		bgcheck = parse_input(input);
		if (args[0] == NULL) {												// If no text recieved, print error
			fprintf(stderr,"No command received\n");
		} else if (strcmp(args[0], "halt") == 0) {		// If command is halt, exit shell
			cont = false;
		} else {
			exec_cmd(bgcheck);													// Fork and execute new process
		}
	}

	return 0;
}

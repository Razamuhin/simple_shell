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
#include "shellfuncts.h"

// Set max length of command
#define MAX_LENGTH 1000

// Declare array to hold command line input
char *args[MAX_LENGTH];

// parse_input - takes user input and breaks it into a matrix of arguments
// *input - pointer to user input
int parse_input(char *input){
	int bgcheck = 0, i = 0;
	input[strlen(input)-1] = '\0';
	args[0] = strtok(input," ");
	while(args[i] != NULL){
		if(*args[i]=='"'){
			args[i]++;
			char *tmp = strtok(NULL,"\"");
			char buffer[100];
			snprintf(buffer, 100, "%s %s",args[i], tmp);
			args[i] = buffer;
		}
		args[i+1] = strtok(NULL," ");
		args[i+2] = NULL;
		printf("Argument %d: '%s'\n",i,args[i]);
		i++;
	}
	if(args[0] != NULL && strcmp(args[i-1],"&")==0){ bgcheck = 1; }
	return bgcheck;
}

// execute shell command
// reference: https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
int exec_cmd(int bgcheck){
	int i = 0, err_chk = 1, status;
	pid_t pid;
	pid = fork();
	if (pid==0) {
		//while
		for(i=0;i<4;i++){
			if (strcmp(args[0], commands[i]) == 0 ) {
				printf("Starting child process %s with pid %d\n",args[0],getpid());
				err_chk = 0;
				printf("%s\n",args[3]);
				return (*cmd[i])(args);
			}
		}
		if (err_chk == 1) {
			fprintf(stderr,"Command not recognized!\n");
			exit(0);
		}
	} else {
		printf("%s\n",args[3]);
		if(bgcheck==0){ waitpid(pid,&status,0); }
	}
	return 0;
}

int main(void){
	// References:
	// https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf
	// https://brennan.io/2015/01/16/write-a-shell-in-c/
	// Allocate memory for user arguments, and exit gracefully if no memory is available.
	char input[MAX_LENGTH];

	//don't need
	if(input == NULL){
		fprintf(stderr,"Out of memory - please download additional RAM\n");
		return 1;
	}

	int bgcheck;
	int cont = 1;	// # CHANGE TO BOOL

	// use getpid() to get and print the process id for this command loop
	printf("Shell pid is %d\n",getpid());
	// prompt user for next command

	while(cont == 1){
		// shell prompt
		printf("wash> ");
		fflush(stdout);
		fgets(input, MAX_LENGTH, stdin);

		// parse command
		bgcheck = parse_input(input);
		printf("%s\n",args[3]);
		if (args[0] == NULL) {												// if no text recieved, print error
			fprintf(stderr,"No command received\n");
		} else if (strcmp(args[0], "halt") == 0) {		// if command is halt, exit shell
			cont = 0;
		} else {
			// fork and execute new process
			exec_cmd(bgcheck);
		}

		// if command is in the foreground, wait for it to complete
		//end loop

	}

	return 0;
}

/*
int parse_input(char *input){
	int bgcheck = 0;
	// Replace newline at end of command with null character
	input[strlen(input)-1] = '\0';
	// test print
	// printf("%s\n",input);

	// split user input into matrix of arguments

	char *arg = strtok(input," ");
	int i = 0;
	while(arg != NULL){
		args[i] = arg;
		arg = strtok(NULL," ");
		i++;
	}
	args[i] = NULL;
	// check whether last argument is '&', set bgcheck flag accordingly
	if(args[0] != NULL && strcmp(args[i-1],"&")==0){ bgcheck = 1; }
	return bgcheck;
}
*/
/*int parse_input(char *input){
	int bgcheck = 0, i = 0;
	input[strlen(input)-1] = '\0';
	char *arg = strtok(input," ");
	//args[0] = strtok(input," ");
	while(arg != NULL){
		if(*arg=='"'){
			arg++;
			char *tmp = strtok(NULL,"\"");
			char buffer[100];
			snprintf(buffer, 100, "%s %s",arg, tmp);
			arg = buffer;
			printf("%s\n",arg);
		}
		args[i]=arg;
		arg=strtok(NULL," ");
		printf("Argument %d: '%s'\n",i,args[i]);
		i++;
	}
	args[i]=NULL;
	//printf("%s\n",args[3]);
	if(args[0] != NULL && strcmp(args[i-1],"&")==0){ bgcheck = 1; }
	return bgcheck;
}*/

/*************************************************************************************
 * shellfuncts.h - header file for your shell functions
 *
 *************************************************************************************/

// Create a new file
int create(char **filename);

// Append text to the named file, n times
int update(char **filename);

// Display contents of named file
int list(char **filename);

// Display files in the current directory
int dir();

char *commands[] = { "create", "update", "list", "dir" };
int (*cmd[]) (char **) = { &create, &update, &list, &dir };

// Terminate the shell

/*************************************************************************************
 * shellfuncts.h - header file for your shell functions
 *
 *************************************************************************************/

// Create a new file
int create(char **arguments);

// Append text to the named file, n times
int update(char **arguments);

// Display contents of named file
int list(char **arguments);

// Display files in the current directory
int dir();

char *commands[] = { "create", "update", "list", "dir", NULL };
int (*cmd[]) (char **) = { &create, &update, &list, &dir, NULL };

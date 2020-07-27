/*************************************************************************************
 * shellfuncts.h - header file for your shell functions
 *
 *************************************************************************************/

// Replace these with something useful
int hello(int param1);
void send_msg(const char *param2);

// Create a new file
int create(char **filename);

// Append text to the named file, n times
int update(char *filename, int n, char *text);

// Display contents of named file
int list(char *filename);

// Display files in the current directory
int dir();

// Terminate the shell

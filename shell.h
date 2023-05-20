#ifndef SHELL_H
#define SHELL_H
/************************************************
 *                                              *
 *              LIBRARIES                       *
 *                                              *
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/************************************************
 *			                        *
 *		MACROS                          *
 *			                        *
 ************************************************/
#define MAX_COMMAND_LENGTH 1024
extern char **environ;


/************************************************
 *			                        *
 *		PROTOTYPES                      *
 *			                        *
 ************************************************/
int cmdexe(char **argv, char **envp);
char *pathfinder(char *cmd);
void read_args(char **argv);
void env(char **envStrings);
void exitShell();

/************************************************
 *			                        *
 *		Structure                       *
 *			                        *
 ************************************************/
/* Allocate memory for the environment variables*/
    typedef struct Env {
        char *key;
        char *val;
    }env_t;

#endif

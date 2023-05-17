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
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

/************************************************
 *			                        *
 *		MACROS                          *
 *			                        *
 ************************************************/
#define MAX_COMMAND_LENGTH 1024


/************************************************
 *			                        *
 *		PROTOTYPES                      *
 *			                        *
 ************************************************/
int cmdexe(char **argv);
char *pathfinder(char *command);

#endif

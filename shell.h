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
#include <stdarg.h>

/************************************************
 *			                        *
 *		MACROS                          *
 *			                        *
 ************************************************/
#define MAX_COMMAND_LENGTH 1024
#define MAX_PATH_LENGTH 1024
extern char **environ;
/*Global Variables */
int count;
char *name;
/************************************************
 *			                        *
 *		PROTOTYPES                      *
 *			                        *
 ************************************************/

char *cmdnf(char **argv);
int cmdexe(char **argv, char **envp);
void _fork(char **argv, char **envp);
char *pathfinder(char *cmd);
void read_args(char **argv);
char **_env(char **envStrings);
void exitShell(void);
char *_cd(const char *path);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
void cd(const char *path);
void _puts(char *str);
void readArg(char **argv);
char *_strndup(const char *str, size_t n);
size_t _strlen(char *s);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
char *_getenv(const char *name);
int _fprintf(int fd, const char *format, ...);
void reverse_string(char *str, int length);
int int_to_string(int num, char *buffer);
int numdl(int n);
char *_itoa(int n);
char **splitui(char *user_input);
char *readui();

/************************************************
 *			                        *
 *		Structure                       *
 *			                        *
 ************************************************/
/**
 * struct env - Allocate memory for the environment variables
 * @key: environ variable
 * @val: environ varaible value.
 */
typedef struct env
{
	char *key;
	char *val;
} env_t;

/**
 * struct list_s - singly linked list
 * @key: string - (malloc'ed string)
 * @val: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *key;
	char *val;
	struct list_s *next;
} list_t;

#endif

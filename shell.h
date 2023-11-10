#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

/* builtins.c */
char *_cd(const char *path);
int exitShell(char **argv);

/* cleanup.c */
void cleaner(char **args);
void env_cleanup(void);
void free_args(char **args);

/* envbin.c */
char **_env(char **envStrings);
int mysetenv(char *name, char *value);
void printEnv(char **envp);


/* errors.c */
int err_gen(char **argv, int err_no);
void cd_error(char *args);
void cd_error2(char *args);
void errexit(char *args);

/*errcode.c */
char *error_127(char **args);

/* misc2.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);
void initialize_buffer(int fd, char *buffer, size_t *pos, size_t *size);
int mygetc(int fd);
int is_absolute_path(const char *path);

/* parser.c */
int run_input(void);
int tokenizer(char *user_input);

/* path.c */
char *_which(char *cmd);
char *build_path(char *cmd, char *patht);
char *_getenv(const char *name);
char *wunset(char *cmd);

/* string.c */
void _puts(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);

/* string2.c */
char *_strdup(const char *str);
char *_strndup(const char *str, size_t n);
char *myitoa(int num);
char *_strtok(char *line, const char *delim);
char *_strchr(const char *str, int character);

/* string3.c */
int _atoi(char *s);
int _strncmp(const char *s1, const char *s2, size_t n);

/* run.c */
int cmdexe(char **argv, char **envp);
int corexec(char **argv);
int extexec(char **argv, char **envp);
int parent_proc(pid_t pid, char **argv);

/*misc.c*/
void sig_h(int signum);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void addFunction(void *ptr);

/* global variables */
int addycount, hist; /* history counter */
int builtpath, path_unset;
char *user_input, *name; /* name of program */
void *envaddys[100];

/* MACROS */
#define MAXPATH_LEN 1024
#define BUFFER_SIZE 1024

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

/*Remove after*/



#endif /*SHELL_H*/

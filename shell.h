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
char *get_dir(const char *path, char **envp);
char *_cd(const char *path);
char **_env(char **envStrings);
void exitShell(char **argv);

/* errors.c */
int err_gen(char **argv, int err_no);
void cd_error(char *args);
void cd_error2(char *args);

/*errcode.c */
char *error_127(char **args);

/* misc2.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);
void initialize_buffer(int fd, char *buffer, size_t *pos, size_t *size);
int mygetc(int fd);

/* parser.c */
int run_input(void);
int tokenizer(char *user_input);

/* path.c */
char *_which(char *cmd);
char *build_path(char *cmd, char *patht);
char *_getenv(const char *name);

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


/* run.c */
int cmdexe(char **argv, char **envp);
int exe_bi_cmd(char **argv);
int exe_ext_cmd(char **argv, char **envp);
int parent_proc(pid_t pid, char **argv);

/*misc.c*/
void sig_h(int signum);
int _atoi(char *s);
void free_args(char **args);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* global variables */
int hist; /* history counter */
int is_absolute_path;
char *name; /* name of program */
char *user_input;
char *prompt;

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

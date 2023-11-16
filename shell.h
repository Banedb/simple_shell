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


/**
 * struct form - Used both for env and alias
 * @name: key
 * @val: value
 */
typedef struct form
{
	char *name;
	char *val;
} PAIR;


/* alias.c */
void alias_handler(char **args);
char *find_alias(char *names, int *index);

void list_alias(int i);
void create_alias(char *names, char *values);


/* builtins.c */
void _cd(char *path);
int exitShell(char **argv);

/* cleanup.c */
void cleaner(char **args);
void env_cleanup(void);
void free_args(char **args);

/* envbin.c */
char **_env(char **envStrings);
int mysetenv(char *name, char *value);
int myunsetenv(char *name);
int printEnv(char **envp);


/* errors.c */
int error_handler(char **argv, int err_no);
char *cd_error(char *args);
void gen_cd_error(char *args, int num);
void errexit(char *args);

/*errcode.c */
char *error_127(char **args);
void ferror_127(char **args);

/* file.c */
int check_file(const char *path);
void run_file(const char *filename);
void varhelper(char **buff, char *str, int num, size_t *index);

/* misc2.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);
void initialize_buffer(int fd, char *buffer, size_t *pos, size_t *size);
int mygetc(int fd);
int is_absolute_path(const char *path);

/* parser.c */
int run_input(void);
int tokenizer(char *user_input);
int parser(char *line);
int checkAND(char *commands);
int checkOR(char *commands);

/* path.c */
char *_which(char *cmd);
char *build_path(char *cmd, char *patht);
char *_getenv(const char *name);


/* string.c */
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strlen(char *s);

/* string2.c */
char *_strdup(const char *str);
char *_strndup(const char *str, size_t n);
char *_strtok(char *line, const char *delim);
char *_strtok_r(char *str, const char *delim, char **saveptr);
char *_strchr(const char *str, int character);

/* string3.c */
int _atoi(char *s);
char *myitoa(int num);
void _puts(char *str);
char *_strstr(char *haystack, char *needle);

/* run.c */
int cmdexe(char **argv);
int corexec(char **argv);
int extexec(char **argv, char **envp);
int parent_proc(pid_t pid, char **argv);

/*misc.c*/
void addyarray(void *ptr);
char *comment(char *line);
void sig_h(int signum);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *repvar(char *source);


/* global variables */
int addycount, aliascount, exit_status, hist; /* history counter */
int builtpath, path_unset, nullvar;
char *user_input, *name; /* name of program */
void *envaddys[100];

/* vars.c */
char *handle_vars(char *command);

/* MACROS */
#define MAXPATH_LEN 1024
#define BUFFER_SIZE 1024
#define MAX_ALIASES 10

PAIR aliases[MAX_ALIASES];

#endif /*SHELL_H*/

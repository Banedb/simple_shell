#include "shell.h"
/**
 * cmdexe - coordinates command execution
 * @argv: array of arguments passed to function
 * @envp: pointer to the environment variables
 * Return: 0 (Success)
 */
int cmdexe(char **argv, char **envp)
{
	int bic;

	if (argv && argv[0])
	{
		bic = exe_bi_cmd(argv);
		if (!bic)
			return (0);
		else
			return (exe_ext_cmd(argv, envp));
	}
	else
		return (0);
}

/**
 * exe_ext_cmd - handles external commands execution
 * @argv: array of arguments passed to function
 * @envp: pointer to the environment variables
 * Return: 0 (Success)
 */

int exe_ext_cmd(char **argv, char **envp)
{
	char *cmd = _which(argv[0]);
	int exex = -1, exit_status = 0;
	pid_t pid;

	if (cmd != NULL) /* fork only when command exists */
	{
		pid = fork();
		if (pid == 0)
		{
			exex = execve(cmd, argv, _env(envp));
			if (exex == -1)
			{
				free(cmd);
				perror("execve");
				return (-1);
			}
		}
		else if (pid == -1)/* fork failed */
		{
			free(cmd);
			perror("fork");
			return (-1);
		}
		else
		{/* parent process */
			free(cmd);
			return (parent_proc(pid, argv));
		}
	}
	else/* cannot locate exe */
		exit_status = err_gen(argv, 127);
	return (exit_status);
}

/**
 * parent_proc - handles parent proccess after fork
 * @argv: array of arguments passed to function
 * @pid: proccess id
 * Return: 0 (Success)
 */

int parent_proc(pid_t pid, char **argv)
{
	int status, exit_status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			err_gen(argv, exit_status);
	}
	else
	{
		exit_status = 2;
		perror("error");
		errno = 2;
	}
	return (exit_status);
}
/**
 * exe_bi_cmd - executes builtin commands
 * @argv: array of arguments passed to function
 *
 * Return: 0 (Success)
 */

int exe_bi_cmd(char **argv)
{
	char *path;

	if (_strcmp(argv[0], "exit") == 0)
		exitShell(argv);
	else if (_strcmp(argv[0], "cd") == 0)
	{
		if (!argv[1])
			path = _cd(argv[1]), chdir(path);
		else
		{
			path = _cd(argv[1]);
			if (path)
				free(path);
		}
		return (0);
	}
	return (-1);
}

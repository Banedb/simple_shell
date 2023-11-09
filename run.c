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
		bic = corexec(argv);
		if ((bic == 0) || (_strcmp(argv[0], "exit") == 0))
			return (bic);
		else
			return (extexec(argv, envp));
	}
	else
		return (0);
}

/**
 * extexec - handles external commands execution
 * @argv: array of arguments passed to function
 * @envp: pointer to the environment variables
 * Return: 0 (Success)
 */

int extexec(char **argv, char **envp)
{
	char *cmdpath = _which(argv[0]);
	int exit_status = 0;
	pid_t pid;

	if (cmdpath != NULL) /* fork only when command exists */
	{
		pid = fork();
		if (pid == 0)
		{/*child process */
			exit_status = execve(cmdpath, argv, _env(envp));
			if (exit_status == -1)
			{
				if (builtpath)
					free(cmdpath);
				perror("execve");
				return (-1);
			}
		}
		else if (pid == -1)/* fork failed */
		{
			if (builtpath)
				free(cmdpath);
			perror("fork");
			return (-1);
		}
		else
		{/* parent process */
			if (builtpath)
				free(cmdpath);
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
	if (WIFEXITED(status)) /*Returns true if child process exited normally*/
	{
		exit_status = WEXITSTATUS(status);/*Retrieve status*/
		if (exit_status != 0)
		{
			err_gen(argv, exit_status);
			/* if in noninteractive mode, exit with exitstatus */
			if (!(isatty(STDIN_FILENO)))
				exit(exit_status);
		}
	}
	else if (WIFSIGNALED(status))/* child process exited due to a signal */
	{
		exit_status = (128 + WTERMSIG(status));
		if (!(isatty(STDIN_FILENO)))
			exit(exit_status);
	}
	else/* child process did not exit normally */
	{
		exit_status = 127;
		if (!(isatty(STDIN_FILENO)))
			exit(exit_status);
	}
	return (exit_status);
}
/**
 * corexec - executes builtin commands
 * @argv: array of arguments passed to function
 *
 * Return: 0 (Success)
 */

int corexec(char **argv)
{
	int check;
	char *path;

	if (_strcmp(argv[0], "exit") == 0)
	{
		check = exitShell(argv);
		return (check);
	}
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
	else if (_strcmp(argv[0], "env") == 0)
	{
		printEnv(environ);
		return (0);
	}
	return (-1);
}

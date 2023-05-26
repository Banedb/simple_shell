#include "shell.h"

/**
 * cmdexe - calls in the execve function to enable command execution
 * @argv: Arguments passed to function
 * an array of pointers to strings,
 * err
 * storing environment varibles and their values
 * Return: 0 (Success)
 */
int execute(char **argv)
{
	pid_t id;
	int status = 0;
	char *path, *envp[2];

	if (!argv  || !*argv)
		return (status);
	/*if (check_for_builtin(argv))
		return (status);*/

	id = fork();
	if (id < 0)
	{
		perror("fork");
		return (1);
	}
	if (id == -1)
		perror(argv[0]);/* free_tokens(argv), free_last_input();*/
	if (id == 0)
	{
		envp[0] = get_path();
		envp[1] = NULL;
		path = NULL;
		if (argv[0][0] != '/')
			path = pathfinder(argv[0]);
		if (!path)
			path = argv[0];
		if (execve(path, argv, envp) == -1)
		{
			perror(argv[0]);/* free_tokens(argv), free_last_input();*/
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		while (1)
		{
			pid_t result = waitpid(id, &status, WUNTRACED);
    
			if (result == -1)
			{
				perror("waitpid");
				exit(1);
			}
			if (WIFEXITED(status) || WIFSIGNALED(status))
			{
				break;
			}
		}

	}
	return (status);
}

#include "shell.h"

/**
 * tokenizeLine - tokenize line
 * @line: user input
 * Return: Array of pointers to strings,
 * containing tokens
 */
char **tokenizeLine(char *line)
{
	char *token, *copy;
	int tokenCount = 0;
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));

	if (tokens == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	/*Make a copy of the line to avoid modifying the original string*/
	copy = strdup(line);
	/*Tokenize the line based on whitespace characters*/
	token = strtok(copy, " \t\n");

	while (token != NULL && tokenCount < MAX_TOKENS)
	{
		/*Store each token in the array*/
		tokens[tokenCount] = strdup(token);
		tokenCount++;
		token = strtok(NULL, " \t\n");
	}
	/*Set the last element of the array to NULL for termination*/
	tokens[tokenCount] = NULL;
	free(copy);  /*Free the memory allocated for the copy*/

	return (tokens);
}

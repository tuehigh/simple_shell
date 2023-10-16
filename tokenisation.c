#include "our_own_shell.h"
/**
* **strtow - splits a string into words. Repeat delimiters are ignored
* @input: the input string
* @delimiter: the delimiter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow(char *input, char *delimiter)
{
int i, j, k, m, numwords = 0;
char **words;

if (input == NULL || input[0] == 0)
return (NULL);
if (!delimiter)
delimiter = " ";
for (i = 0; input[i] != '\0'; i++)
{
if (!is_delim(input[i], delimiter) && (is_delim(input[i + 1],
delimiter) || !input[i + 1]))
numwords++;
}
if (numwords == 0)
return (NULL);
words = malloc((1 + numwords) *sizeof(char *));
if (!words)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (is_delim(input[i], delimiter))
i++;
k = 0;
for (k = 0; !is_delim(input[i + k], delimiter) && input[i + k]; k++)
{
}
words[j] = malloc((k + 1) * sizeof(char));
if (!words[j])
{
for (k = 0; k < j; k++)
free(words[k]);
free(words);
return (NULL);
}
for (m = 0; m < k; m++)
words[j][m] = input[i++];
words[j][m] = 0;
}
words[j] = NULL;
return (words);
}

/**
* **strtow2 - splits a string into words
* @input: the input string
* @delimiter: the delimiter character
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *input, char delimiter)
{
int i, j, k, m, numwords = 0;
char **words;

if (input == NULL || input[0] == 0)
return (NULL);
for (i = 0; input[i] != '\0'; i++)
{
if ((input[i] != delimiter && input[i + 1] == delimiter) ||
(input[i] != delimiter && !input[i + 1]) || input[i + 1] == delimiter)
numwords++;
}
if (numwords == 0)
return (NULL);
words = malloc((1 + numwords) *sizeof(char *));
if (!words)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (input[i] == delimiter && input[i] != delimiter)
i++;
k = 0;
for (k = 0; input[i + k] != delimiter &&
input[i + k] && input[i + k] != delimiter; k++)
{
}
words[j] = malloc((k + 1) * sizeof(char));
if (!words[j])
{
for (k = 0; k < j; k++)
free(words[k]);
free(words);
return (NULL);
}
for (m = 0; m < k; m++)
words[j][m] = input[i++];
words[j][m] = 0;
}
words[j] = NULL;
return (words);
}


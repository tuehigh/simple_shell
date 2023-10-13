#include "shell.h"

/**
* list_len - function that determines length of linked list
* @lst: pointer to first node
*
* Return: size of list
*/
size_t list_len(const list_t *lst)
{
	size_t count = 0;

	for (; lst; lst = lst->next)
		count++;
	return (count);
}

/**
* list_to_strings -functions returns an array of strings of the lst->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t count = list_len(head);
	char **strings;
	char *str;

	if (!head || !count)
		return (NULL);
	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	for (size_t i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[count] = NULL;
	return (strings);
}

/**
* print_list -function to prints all elements of a list_t linked list
* @lst: pointer to first node
*
* Return: size of list
*/
size_t print_list(const list_t *lst)
{
	size_t i = 0;

	for (; lst; lst = lst->next, i++)
	{
		_puts(convert_number(lst->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(lst->str ? lst->str : "(nil)");
		_puts("\n");
	}
	return (i);
}

/**
* node_starts_with - function to returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
*
* Return: match node or null
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *match = NULL;

	for (; node; node = node->next)
	{
		match = starts_with(node->str, prefix);
		if (match && ((c == -1) || (*match == c)))
			return (node);
	}
	return (NULL);
}

/**
* get_node_index -function that gets the index of a node
* @lst: pointer to list head
* @target: pointer to the node
*
* Return: index of node or -1
*/
ssize_t get_node_index(list_t *lst, list_t *target)
{
	size_t index = 0;

	for (; lst; lst = lst->next, index++)
	{
		if (lst == target)
			return (index);
	}
	return (-1);
}

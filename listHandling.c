#include "our_own_shell.h"

/**
* add_node - function that adds a node to the start of the list
* @head: address of pointer to head node
* @data: data for the new node
* @idx: index for history node
*
* Return: size of list
*/
list_t *add_node(list_t **head, const char *data, int idx)
{
	list_t *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = idx;
	if (data)
	{
		new_node->str = _strdup(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
* add_node_end -function to adds a node to the end of the list
* @head: address of pointer to head node
* @data: data for the new node
* @idx: index for history node
*
* Return: size of list
*/
list_t *add_node_end(list_t **head, const char *data, int idx)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = idx;
	if (data)
	{
		new_node->str = _strdup(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		for (; node->next; node = node->next)
		{
/* Loop to the last node */
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
* print_list_str - function to prints only the str
*       element of a list_t linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	for (; h; h = h->next)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		count++;
	}
	return (count);
}

/**
* delete_node_at_index -function to deletes node at given index
* @head: address of pointer to first node
* @index: index of node to delete
*
* Return: 1 on success, 0 on failure
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int idx = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	for (; node; node = node->next)
	{
		if (idx == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		idx++;
		prev_node = node;
	}
	return (0);
}

/**
* free_list - function to free list
* @head: address of pointer to head node
*
* Return: nothing
*/
void free_list(list_t **head)
{
	list_t *node, *next_nd, *current_hd;

	if (!head || !*head)
		return;
	current_hd = *head;
	node = current_hd;
	while (node)
	{
		next_nd = node->next;
		free(node->str);
		free(node);
		node = next_nd;
	}
	*head = NULL;
}

#include "our_own_shell.h"

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


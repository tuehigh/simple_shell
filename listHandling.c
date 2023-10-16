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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:47:34 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 11:23:38 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

//inserts node between two other node, if there is no previous node write NULL
int	node_insert(t_list **new, t_list **prev, t_list **next, t_connect index)
{
	t_list	*next_cpy;

	next_cpy = NULL;
	if (next)
		next_cpy = *next;
	if (prev && *prev)
	{
		(*prev)->next[index] = *new;
		(*new)->prev[index] = *prev;
	}
	if (next_cpy)
	{
		(*new)->next[index] = next_cpy;
		next_cpy->prev[index] = *new;
	}
	return (0);
}

int	add_node(t_list **node, t_list *prev, char *key, char *value)
{
	(*node) = malloc(sizeof(t_list));
	if (!*node)
	{
		if (value)
			free(value);
		return (free(key), 1);
	}
	(*node)->key = key;
	(*node)->value = value;
	(*node)->next = ft_calloc(2, sizeof(t_list *));
	(*node)->prev = ft_calloc(2, sizeof(t_list *));
	(*node)->prev[REGULAR] = prev;
	return (0);
}

void	connect_nodes(t_list ***prev, t_list ***next, t_connect index)
{
	t_list	*tmp;

	if (*next)
		tmp = (*next)[index];
	if ((*prev)[index])
		(*prev)[index]->next[index] = tmp;
	else
		(*prev)[index] = tmp;
	if ((*next)[index])
		(*next)[index]->prev[index] = (*prev)[index];
}

void	replace_node(t_table **table, char *key)
{
	size_t	index;
	t_list	*node;

	index = hash_fnv1(key);
	node = (*table)->nodes[index];
	(*table)->nodes[index] = node->next[REGULAR];
	if ((*table)->nodes[index])
		(*table)->nodes[index]->prev[REGULAR] = NULL;
}

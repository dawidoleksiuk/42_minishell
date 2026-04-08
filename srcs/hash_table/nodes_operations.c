/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:47:34 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 13:40:27 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

//inserts node between two other node, if there is no previous node write NULL
int	node_insert(t_list **new, t_list **prev, t_list *next, char sorted)
{
	if (sorted)
	{
		if (prev && *prev)
			(*prev)->next_sorted = *new;
		(*new)->next_sorted = next;
	}
	else
	{
		if (prev && *prev)
			(*prev)->next = *new;
		(*new)->next = next;
	}
	return (0);
}

int add_node(t_list **node, char *key, char *value)
{
	(*node) = malloc(sizeof(t_list));
	if (!node)
		return (1);
	(*node)->key = key;
	(*node)->value = value;
	(*node)->next = NULL;
	(*node)->next_sorted = NULL;
	return (0);
}
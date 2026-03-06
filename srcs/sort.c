/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:11:47 by alusnia           #+#    #+#             */
/*   Updated: 2026/03/06 07:40:37 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add(t_list **dest, t_list *node, t_list *prev, t_list *next)
{
	if (table_add(dest, node->key, node->value))
		return (1);
	if (prev)
		prev->next = *dest;
	(*dest)->next = next;
	return (0);
}

static int	switch_nodes(t_list **curr, t_list **next)
{
	t_list temp;

	temp.key = (*next)->key;
	temp.value = (*next)->value;
	(*next)->key = (*curr)->key;
	(*next)->value = (*curr)->value;
	(*curr)->key = temp.key;
	(*curr)->value = temp.value;
	return (0);
}

static int find_place(t_list *node, t_list *prev, t_list *curr, t_list *next)
{
	while (curr)
	{
		if (ft_strncmp(node->key, curr->key, ft_strlen(node->key) + 1) < 0)
			return (add(&curr->next, node, prev, curr->next) || switch_nodes(&curr, &curr->next));
		if (!next)
		{
			if (ft_strncmp(node->key, curr->key, ft_strlen(node->key) + 1) > 0)
				return (add(&curr->next, node, curr, curr->next));
			else
				return (add(&curr->next, node, curr, curr->next) || switch_nodes(&curr, &curr->next));
		}
		else if (ft_strncmp(node->key, curr->key, ft_strlen(node->key) + 1) > 0 &&
			ft_strncmp(node->key, next->key, ft_strlen(node->key) + 1) < 0)
			return (add(&curr->next, node, curr, next));
		prev = curr;
		curr = next;
		next = next->next;
	}
	return (0);
}

int	node_sort(t_list **ptr, t_list *node)
{
	t_list	*start;
	t_list	*curr;
	t_list	*prev;

	if (!node)
		return (0);
	if (table_add(&start, node->key, node->value))
		return (1);
	node = node->next;
	while (node)
	{
		curr = start;
		prev = NULL;
		if (find_place(node, prev, curr, curr->next))
		{
			while (start)
			{
				curr = start;
				start = start->next;
				free(curr);
			}
		}
		node = node->next;
	}
	return ((*ptr) = start, 0);
}
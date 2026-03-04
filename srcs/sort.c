/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:11:47 by alusnia           #+#    #+#             */
/*   Updated: 2026/03/04 18:22:12 by alusnia          ###   ########.fr       */
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

static int find_place(t_list **start, t_list *node, t_list *curr, t_list *prev)
{
	while (curr)
	{
		if (!prev)
		{
			if (ft_strncmp(node->key, curr->key, ft_strlen(node->key) + 1) > 0)
				return (add(&curr->next, node, NULL, curr->next));
			else if (!curr->next)
				return (add(start, node, NULL, curr));
		}
		else if (ft_strncmp(node->key, prev->key, ft_strlen(node->key) + 1) > 0 &&
			ft_strncmp(node->key, curr->key, ft_strlen(node->key) + 1) < 0)
			return (add(&prev->next, node, prev, curr));
		else if (!curr->next)
			return (add(&curr->next, node, curr, NULL));
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	node_sort(t_list **ptr, t_list *node)
{
	t_list	*start;
	t_list	*prev;
	t_list	*curr;

	if (!node)
		return (0);
	if (table_add(&start, node->key, node->value))
		return (1);
	node = node->next;
	while (node)
	{
		curr = start;
		prev = NULL;
		if (find_place(&start, node, curr, prev))
		{
			while (start)
			{
				prev = start;
				start = start->next;
				free(prev);
			}
		}
		node = node->next;
	}
	return ((*ptr) = start, 0);
}
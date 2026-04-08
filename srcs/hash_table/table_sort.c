/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:41:28 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 13:33:16 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

static int find_spot(t_list **env, t_list **node)
{
	size_t	len;

	len = ft_strlen((*env)->key);
	if (ft_strisless((*env)->key, (*node)->key, len))
		return (!node_insert(env, NULL, *node, 1));
	else if (!(*node)->next_sorted)
		return (!node_insert(env, node, NULL, 1));
	else if (ft_strismore((*env)->key, (*node)->key, len) && ft_strisless((*env)->key, (*node)->next_sorted->key, len))
		return (!node_insert(env, node, (*node)->next_sorted, 1));
	return (0);
}

void	sort(t_table **table)
{
	t_list	*node;
	t_list	*env_next;
	int		node_moved;

	node = (*table)->sorted_list;
	if ((*table)->env && !(*table)->sorted_list)
	{
		(*table)->sorted_list = (*table)->env;
		(*table)->env = NULL;
	}
	else
	{
		while ((*table)->env)
		{
			env_next = (*table)->env->next_sorted;
			node_moved = 0;
			node_moved = find_spot(&(*table)->env, &node);
			if (node_moved)
				(*table)->env = env_next;
			else
				node = node->next_sorted;
		}
	}
}
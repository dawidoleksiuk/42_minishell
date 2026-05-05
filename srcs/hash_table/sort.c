/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:41:28 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/05 07:52:24 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

int	find_spot(t_list **env, t_list **node)
{
	size_t	len;

	len = ft_strlen((*env)->key);
	if (ft_strisless((*env)->key, (*node)->key, len))
		return (!node_insert(env, NULL, node, SORTED));
	else if (!(*node)->next[SORTED])
		return (!node_insert(env, node, NULL, SORTED));
	else if (ft_strismore((*env)->key, (*node)->key, len)
		&& ft_strisless((*env)->key, (*node)->next[SORTED]->key, len))
		return (!node_insert(env, node, &(*node)->next[SORTED], SORTED));
	return (0);
}

void	sort(t_table **table)
{
	t_list	*node;
	t_list	*debug_node;
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
			//edge case na nowy node mniejszy niz poczatek sorted_list
			debug_node = (*table)->env;
			if (!debug_node)
				debug_node = 0;
			env_next = (*table)->env->next[SORTED];
			node_moved = 0;
			node_moved = find_spot(&(*table)->env, &node);
			if (node_moved)
				(*table)->env = env_next;
			else
				node = node->next[SORTED];
		}
	}
}

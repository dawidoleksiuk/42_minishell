/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:38:37 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 14:27:36 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

static int	add_env(t_table **table, t_list **node)
{
	if (!table || !*table || !node || !*node)
		return (1);
	insert_sorted_list(&(*table)->env, *node);
	return (0);
}

int	table_add(t_table **table, char *key, char *value)
{
	size_t	index;
	t_list	*node;

	index = hash_fnv1(key);
	node = (*table)->nodes[index];
	if (!node)
		return (add_node(&(*table)->nodes[index], NULL, key, value)
			|| add_env(table, &(*table)->nodes[index]));
	while (node->next[REGULAR])
		node = node->next[REGULAR];
	return (add_node(&node->next[REGULAR], node, key, value)
		|| add_env(table, &node->next[REGULAR]));
}

void	display_sorted(t_list *list, int fd)
{
	t_list	*debug_node;

	while (list)
	{
		debug_node = list->next[SORTED];
		if (!debug_node)
			debug_node = 0;
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(list->key, fd);
		if (list->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(list->value, fd);
			ft_putendl_fd("\"", fd);
		}
		else
			ft_putchar_fd('\n', fd);
		list = list->next[SORTED];
	}
}

void	display_regular(t_list **list, int fd)
{
	t_list	*temp;
	size_t	i;

	i = 0;
	while (i < VARIABLES_HASH_BUCKETS)
	{
		if (list[i])
		{
			temp = list[i];
			while (temp)
			{
				if (temp->value)
				{
					ft_putstr_fd(temp->key, fd);
					ft_putchar_fd('=', fd);
					ft_putendl_fd(temp->value, fd);
				}
				temp = temp->next[REGULAR];
			}
		}
		i++;
	}
}

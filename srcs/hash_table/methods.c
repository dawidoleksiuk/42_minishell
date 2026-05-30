/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:54:42 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/30 07:36:18 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

void	display(t_table *table, char sorted, int fd)
{
	if (sorted)
	{
		sort(&table);
		display_sorted(table->sorted_list, fd);
	}
	else
		display_regular(table->nodes, fd);
}

void	del(t_table **table, char *key)
{
	t_list	*node;

	sort(table);
	node = find(*table, key);
	if (!node)
		return ;
	if (!node->prev[REGULAR])
		replace_node(table, key);
	else
		connect_nodes(&node->prev, &node->next, REGULAR);
	if (!node->prev[SORTED])
	{
		if ((*table)->sorted_list == node)
			(*table)->sorted_list = node->next[SORTED];
		if ((*table)->env == node)
			(*table)->env = node->next[SORTED];
	}
	else
		connect_nodes(&node->prev, &node->next, SORTED);
	free_list(node, ONE);
}

char	*get(t_table *table, char *key)
{
	t_list	*node;

	node = find(table, key);
	if (node)
		return (node->value);
	return ("");
}

int	set(t_table **table, char *arg)
{
	char	*key;
	char	*value;
	char	*str;
	t_list	*node;

	str = ft_strdup(arg);
	if (!str || seperate_string(str, &key, &value))
		return (1);
	if (verify_key(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (free(value), free(key), 1);
	}
	node = find(*table, key);
	if (node)
	{
		if (value)
			return (free(key), free(node->value), node->value = value, 0);
		return (free(key), 0);
	}
		
	return (table_add(table, key, value));
}

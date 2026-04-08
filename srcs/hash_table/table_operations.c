/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:38:37 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 13:44:21 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

static t_list	*table_find(t_table *table, char *key)
{
	size_t	index;
	size_t	len;
	t_list	*node;

	len = ft_strlen(key);
	index = hash_fnv1(key);
	node = table->nodes[index];
	while (node && !ft_strisequal(node->key ,key, len))
		node = node->next;
	return (node);
}

char	*table_get(t_table *table, char *key)
{
	t_list	*node;

	node = table_find(table, key);
	if (node)
		return (node->value);
	return (NULL);
}

static int add_env(t_table **table, t_list **node)
{
	t_list	*env;
	size_t	len;

	env = (*table)->env;
	if (!env)
		return ((*table)->env = *node, 0);
	len = ft_strlen((*node)->key);
	while (env->next_sorted && ft_strismore((*node)->key, env->key, len))
		env = env->next_sorted;
	return (node_insert(node, &env, env->next_sorted, 1));
}

int table_add(t_table **table, char *key, char *value)
{
	size_t	index;
	t_list	*node;

	index = hash_fnv1(key);
	node = (*table)->nodes[index];
	if (!node)
		return (add_node(&(*table)->nodes[index], key, value) || add_env(table, &(*table)->nodes[index]));
	while (node->next)
		node = node->next;
	return (add_node(&node->next, key, value) || add_env(table, &node->next));
}

int	table_set(t_table **table, char *str)
{
	char	*key;
	char	*value;
	t_list	*node;

	str = ft_strdup(str);
	if (!str || seperate_string(str, &key, &value))
		return (1);
	if (verify_key(key))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		if (value)
			free(value);
		free(key);
		return (1);
	}
	node = table_find(*table, key);
	if (node)
		return (free(key), free(node->value), node->value = value, 0);
	return (table_add(table, key, value));
}

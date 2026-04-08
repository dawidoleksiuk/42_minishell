/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:38:37 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 18:20:28 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

static int add_env(t_table **table, t_list **node)
{
	t_list	*env;
	size_t	len;

	env = (*table)->env;
	if (!env)
		return ((*table)->env = *node, 0);
	len = ft_strlen((*node)->key);
	while (env->next[SORTED] && ft_strismore((*node)->key, env->key, len))
		env = env->next[SORTED];
	return (node_insert(node, &env, &env->next[SORTED], SORTED));
}

int table_add(t_table **table, char *key, char *value)
{
	size_t	index;
	t_list	*node;

	index = hash_fnv1(key);
	node = (*table)->nodes[index];
	if (!node)
		return (add_node(&(*table)->nodes[index], NULL, key, value) || add_env(table, &(*table)->nodes[index]));
	while (node->next[REGULAR])
		node = node->next[REGULAR];
	return (add_node(&node->next[REGULAR], node, key, value) || add_env(table, &node->next[REGULAR]));
}

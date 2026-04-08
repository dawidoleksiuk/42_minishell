/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:54:42 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 18:27:55 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

static t_list	*find(t_table *table, char *key)
{
	size_t	index;
	size_t	len;
	t_list	*node;

	len = ft_strlen(key);
	index = hash_fnv1(key);
	node = table->nodes[index];
	while (node && !ft_strisequal(node->key ,key, len))
		node = node->next[REGULAR];
	return (node);
}

// void	del(t_table **table, char *key)
// {
// 	t_list	*node;

// 	node = find(*table, key);
// 	if (!node)
// 		return ;
	
// }

char	*get(t_table *table, char *key)
{
	t_list	*node;

	node = find(table, key);
	if (node)
		return (node->value);
	return (NULL);
}

int	set(t_table **table, char *str)
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
	node = find(*table, key);
	if (node)
		return (free(key), free(node->value), node->value = value, 0);
	return (table_add(table, key, value));
}
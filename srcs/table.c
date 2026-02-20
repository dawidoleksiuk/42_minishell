/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:58:13 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/20 12:00:53 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**init_table(char **envp)
{
	t_list	**table;
	ssize_t	i;
	char	*key;
	char	*value;

	table = ft_calloc(63, sizeof(t_list*));
	while (envp && *envp)
	{
		key = *envp;
		value = NULL;
		i = table_get_i(*key);
		if (i < 0)
			table_clear(table);
		if (table_sep_string(key, &key, &value))
			return (table_clear(table), NULL);
		if (table_mod(&table[i], key, value))
			return (table_clear(table), NULL);
		envp++;
	}
	return (table);
}

int	table_mod(t_list **ptr, char *key, char *value)
{
	t_list	*node;
	t_list	*prev;

	node = *ptr;
	if (!node)
		return (table_add(ptr, key, value));
	while (node && ft_strncmp(node->key, key, ft_strlen(key) + 1))
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return (table_add(&prev->next, key, value));
	else
	{
		free(node->value);
		node->value = value;
	}
	return (0);
}

int	table_add(t_list **node, char *key, char *value)
{
	*node = table_new_node(*node);
	if (!node)
		return (1);
	(*node)->key = key;
	(*node)->value = value;
	return (0);
}

t_list	*table_del(t_list *ptr, char *key)
{
	t_list	*node;
	t_list	*prev;

	prev = NULL;
	node = ptr;
	while (node && ft_strncmp(node->key, key, ft_strlen(key) + 1))
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return (ptr);
	if (prev)
	{
		prev->next = node->next;
		clear_node(node);
		return (ptr);
	}
	prev = node->next;
	clear_node(node);
	return (prev);
}

void	table_clear(t_list **table)
{
	size_t	i;

	i = 0;
	while (i < 63)
	{
		if (table[i])
			table[i] = table_del(table[i], table[i]->key);
		else
			i++;
	}
	free(table);
}
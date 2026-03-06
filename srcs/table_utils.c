/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:36:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/03/06 08:22:42 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	table_get_i(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isupper(c))
		return(c - 'A' + 10);
	else if (ft_islower(c))
		return (c - 'a' + 37);
	else if (c == '_')
		return (36);
	return (-1);
}

void	clear_node(t_list *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

t_list *table_new_node(t_list *node)
{
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

int	table_sep_string(char *str, char **key, char **value)
{
	char	*sep;

	sep = ft_strchr(str, '=');
	if (sep && sep[1])
	{
		*key = ft_substr(str, 0, sep - str);
		if (!(*key))
			return (1);
		*value = ft_strdup(sep + 1);
		if (!(*value))
			return (1);
		return (0);
	}
	*key = ft_strdup(str);
	if (!(*key))
		return (1);
	*value = NULL;
	return (0);
}

t_list *table_find_node(t_list **table, char *key)
{
	ssize_t	i;
	t_list	*node;

	i = table_get_i(key[0]);
	if (i < 0)
		return (NULL);
	node = table[i];
	while(node && ft_strncmp(node->key, key, ft_strlen(key) + 1))
		node = node->next;
	return (node);
}

char	*table_find_value(t_list **table, char *key)
{
	t_list	*node;

	node = table_find_node(table, key);
	if (!node)
		return (NULL);
	return (node->value);
}
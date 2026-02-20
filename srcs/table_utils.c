/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:36:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/18 15:17:01 by alusnia          ###   ########.fr       */
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
	if (sep)
	{
		*key = ft_substr(str, 0, sep - str);
		*value = ft_strdup(sep);
		if (!(*key) || !(*value))
			return (1);
		return (0);
	}
	*key = ft_strdup(str);
	*value = ft_calloc(1, sizeof(char));
	if (!(*key) || !(*value))
		return (1);
	return (0);
}

char	*table_find_value(t_list **table, char *key)
{
	size_t	i;
	t_list	*node;

	i = table_get_i(key[0]);
	node = table[i];
	while(node && ft_strncmp(node->key, key, ft_strlen(key) + 1))
		node = node->next;
	if (!node)
		return (NULL);
	return (node->value);
}


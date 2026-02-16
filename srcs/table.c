/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:58:13 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/16 19:29:15 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	table_get_i(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isupper(c))
		return(c - 'A' + 10);
	else if (ft_islower(c))
		return (c - 'a' + 37);
	else if (c == '_')
		return (36);
}

int	table_add(t_list *ptr, char str)
{
	char	*sep;
	size_t	len;

	if (!str)
		return (1);
	sep = ft_strchr(str, '=');
	ptr->key = ft_substr(str, 0, sep - str);
	if (!ptr->key)
		return (1);
	len = ft_strlen(sep);
	if (len)
	{
		ptr->value = ft_substr(sep, 1, len);
		if (!ptr->value)
			return (1);
	}
	else
		ptr->value = NULL;
	return (0);
}
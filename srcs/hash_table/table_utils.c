/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:36:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 13:09:29 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hash_table_internal.h"


/*hashing algorythm used in shell, uses XOR to switch bits. XOR example:
0 XOR 0 = 0 | 1 XOR 1 = 0 | 0 XOR 1 = 1 | 1 XOR 0 = 1*/
size_t	hash_fnv1(char *key)
{
	unsigned int	hash;

	hash = 2166136261u;
	while (*key)
	{
		hash ^= (unsigned char)(*key);
		hash *= FNV_PRIME;
		key++;
	}
	return (hash % VARIABLES_HASH_BUCKETS);
}

int	seperate_string(char *str, char **key, char **value)
{
	char *ptr;

	ptr = ft_strchr(str, '=');
	if (!ptr)
		return (*key = str, *value = NULL, 0);
	ptr[0] = '\0';
	if (!ptr[1])
	{
		*key = str;
		*value = ft_calloc(1, sizeof(char));
		if (!*value)
			return (free(str), 1);
		return (0); 
	}
	*key = ft_strdup(str);
	if (!*key)
		return (free(str), 1);
	*value = ft_strdup(ptr + 1);
	if (!*value)
		return (free(*key), free(str), 1);
	return (free(str), 0);
}

int verify_key(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (1);
	while (++key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (1);
	}
	return (0);
}

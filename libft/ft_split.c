/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:45:46 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/27 10:56:38 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_arr(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

static char	**make_split(char **ptr, char *start, size_t *i, ssize_t j)
{
	if (start[j] != 0 && (j == 0 || start[j - 1] == 0))
	{
		ptr[*i - 1] = ft_strdup(start + j);
		if (!ptr[*i - 1])
			return (free_arr(ptr));
		(*i)--;
	}
	return (ptr);
}

static char	**sep_arr(char *s, char c, size_t *k)
{
	char	**ptr;
	char	*start;
	size_t	i;
	size_t	j;

	ptr = NULL;
	i = 1;
	j = ft_strlen(s);
	if (j == 0)
	{
		ptr = ft_calloc(1, sizeof(char *));
		return (ptr);
	}
	start = s;
	while (j > 1)
	{
		if (start[--j] == c && (j == 0 || start[j - 1] != c))
			i++;
		if (start[j] == c)
			start[j] = '\0';
	}
	ptr = ft_calloc(i + 1, sizeof(char *));
	*k = i;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*start;
	char	d[2];
	size_t	i;
	ssize_t	j;

	i = 0;
	d[0] = c;
	d[1] = '\0';
	start = ft_strtrim(s, d);
	j = ft_strlen(start) + 1;
	ptr = NULL;
	ptr = sep_arr(start, c, &i);
	if (i != 0 && ptr)
	{
		while (i > 0 && --j >= 0 && ptr)
			ptr = make_split(ptr, start, &i, j);
	}
	free(start);
	return (ptr);
}

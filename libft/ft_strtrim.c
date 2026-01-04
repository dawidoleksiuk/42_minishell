/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:10:39 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/09 15:27:56 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_string(char *start, char *end)
{
	char	*ptr;

	ptr = NULL;
	ptr = ft_calloc(end - start + 2, sizeof(char));
	if (ptr)
		ft_memcpy(ptr, start, end - start + 1);
	return (ptr);
}

static char	*move_ptr(char *ptr, int flag, size_t *i)
{
	ptr += flag;
	*i = 0;
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	i = 0;
	while (i < ft_strlen(set))
	{
		if (start == end && *start == set[i])
			return (ft_calloc(1, sizeof(char)));
		else if (*start == set[i])
			start = move_ptr(start, 1, &i);
		else if (*end == set[i])
			end = move_ptr(end, -1, &i);
		else
			i++;
	}
	return (new_string(start, end));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:05:15 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/06 07:02:37 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	p = (char *)big;
	j = ft_strlen(little);
	if (j == 0)
	{
		return (p);
	}
	while (i + j <= len && big[i])
	{
		if (ft_strncmp(big + i, little, j) == 0)
			return (p + i);
		i++;
	}
	return (NULL);
}

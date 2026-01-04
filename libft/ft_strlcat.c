/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:33:22 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/02 11:23:06 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	j = ft_strlen(dst);
	if (j >= size)
		j = size;
	if (j == size)
		return (j + i);
	if (i < size - j)
		ft_memcpy(dst + j, src, i + 1);
	else
	{
		ft_memcpy(dst + j, src, size - j - 1);
		dst[size - 1] = '\0';
	}
	return (i + j);
}

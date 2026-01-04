/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:07:29 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/06 06:59:34 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	while (i < n)
	{
		x = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (x != 0)
			break ;
		i++;
	}
	return (x);
}

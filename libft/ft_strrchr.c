/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 08:08:54 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/08 14:10:01 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	c = (char)c;
	p = NULL;
	while (*s != '\0')
	{
		if (*s == c)
		{
			p = (char *)s;
		}
		s++;
	}
	if (c == '\0')
		p = (char *)s;
	return (p);
}

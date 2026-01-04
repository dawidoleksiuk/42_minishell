/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 07:18:37 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/08 14:06:50 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	c = (char)c;
	p = NULL;
	while (*s != '\0')
	{
		if (*s == c)
		{
			p = (char *)s;
			return (p);
		}
		s++;
	}
	if (c == '\0')
		p = (char *)s;
	return (p);
}

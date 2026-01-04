/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 07:43:56 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/06 07:26:08 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	ptr = NULL;
	i = 0;
	ptr = ft_strdup(s);
	if (ptr)
	{
		while (ptr[i])
		{
			ptr[i] = (f)(i, ptr[i]);
			i++;
		}
	}
	return (ptr);
}

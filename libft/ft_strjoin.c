/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:45:45 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/25 12:42:24 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	ptr = NULL;
	ptr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (ptr)
	{
		ft_memcpy(ptr, s1, ft_strlen(s1));
		ft_memcpy(ptr + ft_strlen(s1), s2, ft_strlen(s2));
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:40:32 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/09 14:54:08 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = NULL;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if ((size_t)start > i)
		start = i;
	if ((size_t)start + len >= i)
		len = i - start;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (ptr)
		ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

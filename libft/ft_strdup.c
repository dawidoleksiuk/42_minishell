/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:14:17 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/08 10:47:26 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = NULL;
	ptr = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (ptr)
		ft_memcpy(ptr, s, ft_strlen(s));
	return (ptr);
}

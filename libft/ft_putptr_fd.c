/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:10:55 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/29 15:42:24 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	int	count;

	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	count = ft_putstr_fd("0x", fd);
	count += ft_puthex_fd((unsigned long)ptr, fd, 0);
	return (count);
}

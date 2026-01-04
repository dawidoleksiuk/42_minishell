/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:48:28 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/28 20:45:42 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_fd(unsigned long n, int fd, char c)
{
	char	base[16];
	int		count;

	count = 1;
	if (c == 0)
		ft_strlcpy(base, "0123456789abcdef", 17);
	else
		ft_strlcpy(base, "0123456789ABCDEF", 17);
	if (n >= 16)
		count += ft_puthex_fd(n / 16, fd, c);
	ft_putchar_fd(base[n % 16], fd);
	return (count);
}

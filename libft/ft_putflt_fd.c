/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:10:07 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/12 09:47:22 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putflt_fd(float n, int fd)
{
	int	count;
	int	decpoint;

	count = 0;
	decpoint = 1000000;
	if (n < 0 && n > -1)
	{
		count = ft_putchar_fd('-', fd);
		n *= -1;
	}
	count += ft_putnbr_fd((int)n, fd);
	n -= (int)n;
	n *= decpoint;
	if (n < 0)
		n *= -1;
	count++;
	ft_putchar_fd('.', fd);
	while (n < decpoint / 10)
	{
		count += ft_putchar_fd('0', fd);
		decpoint /= 10;
	}
	count += ft_putnbr_fd((int)n, fd);
	return (count);
}

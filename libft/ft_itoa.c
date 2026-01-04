/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:08:18 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/06 07:25:16 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*assign_arr(int n, int	*m)
{
	int	i;

	i = 0;
	if (n == INT_MIN)
		return (ft_calloc(12, sizeof(char)));
	else if (n < 0)
		i++;
	else if (n == 0)
		return (ft_calloc(2, sizeof(char)));
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	*m = i - 1;
	return (ft_calloc(i + 1, sizeof(char)));
}

static char	*export_val(char *ptr, int n, int i)
{
	ptr[i] = '0';
	if (n == INT_MIN)
	{
		ft_memcpy(ptr, "-2147483648", 12);
		return (ptr);
	}
	else if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		ptr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	ptr = assign_arr(n, &i);
	if (ptr)
		return (export_val(ptr, n, i));
	return (ptr);
}

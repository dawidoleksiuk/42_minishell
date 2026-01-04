/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:55:08 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/13 11:47:59 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	add_decimal(const char *nptr)
{
	double	x;
	size_t	i;

	x = 0;
	i = 0;
	while (ft_isdigit(nptr[i]))
	{
		x = (x * 10) + (nptr[i++] - '0');
	}
	while (i > 0)
	{
		x /= 10;
		i--;
	}
	return (x);
}

double	ft_atod(const char *nptr)
{
	double		x;
	int			sign;
	size_t		i;

	x = 0;
	sign = 1;
	i = 0;
	while (nptr[i])
	{
		if ((ft_isspace(nptr[i]) || nptr[i] == '+')
			&& (i == 0 || ft_isspace(nptr[i - 1])))
			i++;
		else if (nptr[i] == '-' && (i == 0 || ft_isspace(nptr[i - 1])))
		{
			sign = -1;
			i++;
		}
		else if (ft_isdigit(nptr[i]) != 0)
			x = (x * 10) + (nptr[i++] - '0');
		else
			break ;
	}
	x += add_decimal(nptr + i + 1);
	return (x * sign);
}

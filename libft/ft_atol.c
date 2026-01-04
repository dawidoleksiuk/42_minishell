/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:38:44 by alusnia           #+#    #+#             */
/*   Updated: 2025/11/14 12:48:48 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	x;
	int		sign;
	size_t	i;

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
		else if (ft_isdigit(nptr[i]) != 0 && x == (x * 10) / 10)
			x = (x * 10) + (nptr[i++] - '0');
		else
			break ;
	}
	return (x * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:54:00 by alusnia           #+#    #+#             */
/*   Updated: 2026/06/03 07:42:57 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env_table *table, int fd)
{
	table->display(table->table, 0, fd);
}

void	ft_unset(t_env_table **table, char **args)
{
	while (*args)
	{
		(*table)->del(&(*table)->table, *args);
		args++;
	}
}

void	ft_export(t_exec_info *exec, t_env_table **table, char **args, int fd)
{
	size_t	i;

	if (!args[1])
		(*table)->display((*table)->table, 1, fd);
	else
	{
		i = 1;
		while (args[i])
		{
			if ((*table)->set(&(*table)->table, args[i]))
				exec->error = 1;
			i++;
		}
	}
}

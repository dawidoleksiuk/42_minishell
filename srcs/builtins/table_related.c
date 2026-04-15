/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:54:00 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 20:21:54 by alusnia          ###   ########.fr       */
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
	if (!args[1])
		(*table)->display((*table)->table, 1, fd);
	else
		if ((*table)->set(&(*table)->table, args[1]))
			exec->error = 1;
}
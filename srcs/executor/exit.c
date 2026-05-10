/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 14:42:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 14:49:30 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exec(t_exec_info *exec_info,
			char *msg, int exit_code, void *bonus)
{
	if (bonus)
		free(bonus);
	if (exec_info->pipe_fd)
		free(exec_info->pipe_fd);
	if (exec_info->path)
		free(exec_info->path);
	exec_info->pipe_fd = NULL;
	exec_info->path = NULL;
	exec_info->temp = NULL;
	exec_info->in = 0;
	exec_info->out = 0;
	exec_info->error = 0;
	if (exec_info->args)
	{
		free(exec_info->args);
		exec_info->args = NULL;
	}
	if (msg && ft_strlen(msg))
	{
		ft_putstr_fd(exec_info->cmd->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (msg || exit_code)
		clean_exit(exec_info->data, NULL, exit_code);
}

void	clean_envars(t_envar *envars)
{
	size_t	i;

	if (envars->curr_dir)
		free(envars->curr_dir);
	if (envars->catalogs)
	{
		i = 0;
		while (envars->catalogs[i])
			free(envars->catalogs[i++]);
		free(envars->catalogs);
		envars->catalogs = NULL;
	}
	free(envars);
}

void	clean_exit_executor(t_exec_info *exec_info)
{
	if (exec_info->envars->table)
		exec_info->envars->table->clear(exec_info->envars->table);
	if (exec_info && exec_info->envars)
		clean_envars(exec_info->envars);
	if (exec_info && exec_info->pipe_fd)
		free(exec_info->pipe_fd);
	if (exec_info)
		free(exec_info);
}

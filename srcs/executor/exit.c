/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 14:42:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/06/03 05:40:17 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//msg == NULL clean_exit won't run if exit_code != 0
//msg == "" clean_exit will run -> children will free data memory
void	clean_exec(t_exec_info *exec_info,
			char *msg, int exit_code, void *bonus)
{
	if (bonus)
		free(bonus);
	if (exec_info->path)
		free(exec_info->path);
	exec_info->path = NULL;
	exec_info->temp = NULL;
	exec_info->in = 0;
	exec_info->out = 0;
	exec_info->error = 0;
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
	if (envars->curr_dir)
		free(envars->curr_dir);
	free(envars);
}

void	clean_exit_executor(t_exec_info *exec_info)
{
	if (exec_info->data->table)
		exec_info->data->table->clear(exec_info->data->table);
	if (exec_info && exec_info->envars)
		clean_envars(exec_info->envars);
	if (exec_info)
		free(exec_info);
}

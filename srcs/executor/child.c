/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:17:07 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/05 07:10:24 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	set_up_child(t_data *data, t_exec_info *exec_info, t_cmd *cmd)
{
	set_terminal_settings(data, 1);
	if (setup_signal(SIGINT, SIG_DFL) || setup_signal(SIGQUIT, SIG_DFL))
		clean_exec(data->exec_info, NULL, 1, NULL);
	dup2(exec_info->in, 0);
	if (exec_info->redir_out)
		dup2(exec_info->out, 1);
	else if (cmd->next)
		dup2(exec_info->pipe_fd[1], 1);
	close(exec_info->pipe_fd[0]);
}

void	do_your_job(t_data *data, t_exec_info *exec_info, t_cmd *cmd)
{
	exec_info->args = filtr_cmd(cmd);
	if (!exec_info->args)
		return (clean_exec(exec_info, "malloc failed\n", 1, NULL));
	if (!exec_info->args[0])
		return (clean_exec(exec_info, "", 0, NULL));
	if (check_for_built_ins(data, cmd))
		return (clean_exec(data->exec_info, "", 0, NULL));
	exec_info->path = check_path(exec_info, exec_info->args);
	if (!exec_info->path)
		iter_catalogs(exec_info);
	if (!exec_info->path)
		clean_exec(exec_info, "command not found\n", 127, NULL);
	execve(exec_info->path, exec_info->cmd->args, exec_info->envars->envp);
	clean_exec(exec_info, "execve() failed\n", 1, NULL);
}

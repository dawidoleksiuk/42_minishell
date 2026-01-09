/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/09 19:17:44 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_fd	*give_birth(t_fd *f_info, t_cmd *cmd)
{
	if (cmd->redirs)
		/*errorhandler needed*/redirection(f_info, cmd->redirs, cmd->args[0]);
	if (pipe(f_info->pipe_fd[0]) == -1)
		return (NULL);
	f_info->pid = fork();
	if (f_info->pid == -1)
		return (NULL);
	else if (f_info->pid == 0)
	{
		dup2(f_info->in, 0);
		close(f_info->in);
		if (cmd->redirs == P_REDIR_OUT || cmd->redirs == P_APPEND)
			dup2(f_info->out, )
		dup2(f_info->pipe_fd[1], 1)
	}
	else 
	{

	}
}

void	exec_command(t_cmd *start_cmd, t_fd *f_info)
{
	t_cmd *cmd;

	cmd = start_cmd;
	while (cmd)
	{
		f_info = give_birth(f_info, cmd);
	}

}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/15 20:22:41 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_fd	*give_birth(t_fd *f_info, t_cmd *cmd)
{
	if (cmd->redirs)
		f_info->error = redirection(f_info, cmd->redirs, cmd->args[0]);
	if (f_info->error || pipe(f_info->pipe_fd[0]) == -1)
		return (f_info->error += f_info->error == 0, f_info);
	f_info->pid = fork();
	if (f_info->pid == -1)
		return (NULL);
	else if (f_info->pid == 0)
	{
		dup2(f_info->in, 0);
		close(f_info->in);
		if (cmd->redirs == P_REDIR_OUT || cmd->redirs == P_APPEND)
			dup2(f_info->out, );
		dup2(f_info->pipe_fd[1], 1)
	}
	else 
	{
	}
}

void	executor(t_cmd *start_cmd, t_fd *f_info, int *exit_code)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;

	cmd = start_cmd;
	while (cmd)
	{
		f_info = give_birth(f_info, cmd);
		if (f_info->pid == 0)
			do_your_job();
		cmd = cmd->next;
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == f_info->pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		pid = waitpid(-1, &status, 0);
	}
}


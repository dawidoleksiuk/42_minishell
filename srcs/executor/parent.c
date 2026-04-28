/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:19:55 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/28 11:41:37 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

unsigned char	translate_status(pid_t data_pid, pid_t pid,
				int status, unsigned char error)
{
	int				sig;
	unsigned char	exit_code;

	if (pid == data_pid)
	{
		if (WIFEXITED(status) && !error)
			exit_code = WEXITSTATUS(status);
		else
			exit_code = error;
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				g_signum = sig;
				write(1, "\n", 1);
			}
			if (sig == SIGQUIT)
			{
				g_signum = sig;
				write(1, "Quit (core dumped)\n", 20);
			}
		}
	}
	return (exit_code);
}

void	check_out_children(t_exec_info *exec_info, int *exit_code)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (isatty(STDIN_FILENO))
		if (setup_signal(SIGINT, &sig_handler)
			|| setup_signal(SIGQUIT, SIG_IGN))
			return (clean_exec(exec_info, NULL, 0, NULL));
	while (pid > 0)
	{
		*exit_code = translate_status(exec_info->pid, pid,
				status, exec_info->error);
		pid = waitpid(-1, &status, 0);
	}
}

t_exec_info	*give_birth(t_data *data, t_exec_info *exec_info, t_cmd *cmd)
{
	exec_info = redir(exec_info, cmd->redirs);
	if (g_signum)
		return (exec_info);
	if (exec_info->error || pipe(exec_info->pipe_fd) == -1)
		return (exec_info->error += exec_info->error == 0, exec_info);
	exec_info->pid = fork();
	if (exec_info->pid == -1)
		return (exec_info->error = 1, exec_info);
	if (setup_signal(SIGINT, SIG_IGN) || setup_signal(SIGQUIT, SIG_IGN))
		return (exec_info);
	else if (exec_info->pid == IS_CHILD)
		set_up_child(data, exec_info, cmd);
	else
	{
		if (exec_info->in)
			close(exec_info->in);
		close(exec_info->pipe_fd[1]);
		exec_info->in = exec_info->pipe_fd[0];
		exec_info->out = 1;
	}
	return (exec_info);
}

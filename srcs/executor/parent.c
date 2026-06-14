/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:19:55 by alusnia           #+#    #+#             */
/*   Updated: 2026/06/14 15:20:47 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	manage_signal(int status)
{
	int				sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT)
	{
		g_signum = sig;
		ft_putendl_fd("", 2);
	}
	if (sig == SIGQUIT)
	{
		g_signum = sig;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
}

unsigned char	translate_status(pid_t data_pid, pid_t pid,
				int status, unsigned char error)
{
	unsigned char	exit_code;

	exit_code = 0;
	if (pid == data_pid)
	{
		if (WIFEXITED(status) && !error)
			exit_code = WEXITSTATUS(status);
		else
			exit_code = error;
		if (WIFSIGNALED(status))
			manage_signal(status);
	}
	return (exit_code);
}

void	check_out_children(t_exec_info *exec_info, int *exit_code)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = waitpid(-1, &status, 0);
	if (isatty(STDIN_FILENO))
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW,
				&exec_info->data->termios_p_save) != 0)
			return (clean_exec(exec_info, "disable_echoctl failed\n", 1, NULL));
		if (disable_echoctl() != 0)
			return (clean_exec(exec_info, "disable_echoctl failed\n", 1, NULL));
		if (setup_signal(SIGINT, &sig_handler)
			|| setup_signal(SIGQUIT, SIG_IGN))
			return (clean_exec(exec_info, NULL, 0, NULL));
	}
	while (pid > 0)
	{
		*exit_code = translate_status(exec_info->pid, pid,
				status, exec_info->error);
		pid = waitpid(-1, &status, 0);
	}
}

static t_exec_info	*prepare_for_labor(t_exec_info *exec_info, t_cmd *cmd)
{
	exec_info = redir(exec_info, cmd->redirs);
	if (g_signum)
		return (exec_info);
	if (pipe(exec_info->pipe_fd) == -1)
		return (exec_info->error += exec_info->error == 0, exec_info);
	return (exec_info);
}

t_exec_info	*give_birth(t_data *data, t_exec_info *exec_info, t_cmd *cmd)
{
	exec_info = prepare_for_labor(exec_info, cmd);
	if (exec_info->error)
	{
		if (exec_info->in)
			close(exec_info->in);
		return (exec_info->in = exec_info->pipe_fd[0],
			close(exec_info->pipe_fd[1]), exec_info);
	}
	exec_info->pid = fork();
	if (exec_info->pid == -1)
		return (exec_info->error = 1, exec_info);
	if (setup_signal(SIGINT, SIG_IGN) || setup_signal(SIGQUIT, SIG_IGN))
		return (exec_info);
	if (exec_info->pid == IS_CHILD)
		set_up_child(data, exec_info, cmd);
	else
	{
		if (exec_info->in)
			close(exec_info->in);
		close(exec_info->pipe_fd[1]);
		exec_info->in = exec_info->pipe_fd[0];
	}
	return (exec_info);
}

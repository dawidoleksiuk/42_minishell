/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:19:55 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/18 11:24:21 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static unsigned char	translate_status(pid_t data_pid, pid_t pid, int status, unsigned char error)
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

void	check_out_children(t_exec_info *exec_info, unsigned char *exit_code)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (isatty(STDIN_FILENO))
		if (setup_signal(SIGINT, &sig_handler) || setup_signal(SIGQUIT, SIG_IGN))
			return (clean_exec(exec_info, NULL, 0, NULL));
	while (pid > 0)
	{
		*exit_code = translate_status(exec_info->pid, pid, status, exec_info->error);
		pid = waitpid(-1, &status, 0);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/23 15:18:40 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *check_path(t_exec_info *exec_info)
{
	char	*str;

	if (exec_info->cmd->args[0][0] == '~' && exec_info->home_dir)
	{
		str = ft_strjoin(exec_info->home_dir, exec_info->cmd->args[0]);
		if (!str)
			kill_process(exec_info, 1, NULL);
	}
	if (access(str, F_OK) == 1)
		return (free(str), NULL);
	if (access(str, X_OK) == 1)
		kill_process(exec_info, 126, str);
	return (str);
}

static void	do_your_job(t_exec_info *exec_info)
{
	size_t	i;

	i = 0;
	exec_info->path = check_path(exec_info);
	if (!exec_info->path)
	{
		while (exec_info->catalogs && exec_info->catalogs[i] && !exec_info->path)
		{
			exec_info->temp = exec_info->catalogs[i++];
			if (!exec_info->temp)
				kill_proccess(exec_info, 3, NULL);
			exec_info = check_catalogs(exec_info, exec_info->temp, ft_strjoin("/", exec_info->cmd->args[0]));
		}  
	}
	if (!exec_info->path)
		kill_proccess(exec_info, 127, NULL);
	execve(exec_info->path, exec_info->cmd->args[1], exec_info->envp);
	perror("execve() failed\n");
	kill_process(exec_info, 1, NULL);
}

t_exec_info	*give_birth(t_exec_info *exec_info, t_cmd *cmd)
{
	exec_info = redir(exec_info, cmd->redirs);
	if (exec_info->error || pipe(exec_info->pipe_fd[0]) == -1)
		return (exec_info->error += exec_info->error == 0, exec_info);
	exec_info->pid = fork();
	if (exec_info->pid == -1)
		return (exec_info->error = 1, exec_info);
	else if (exec_info->pid == 0)
	{
		dup2(exec_info->in, 0);
		close(exec_info->in);
		if (cmd->redirs->type == REDIR_OUT || cmd->redirs->type == APPEND)
			dup2(exec_info->out, );
		dup2(exec_info->pipe_fd[1], 1);
	}
	else
	{
		
	}
}

void	executor(t_cmd *cmd_head, t_exec_info *exec_info, int *exit_code)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;

	cmd = cmd_head;
	while (cmd)
	{
		exec_info->cmd = cmd;
		exec_info = give_birth(exec_info, cmd->args);
		if (exec_info->error)
			break;
		if (exec_info->pid == 0)
			do_your_job(exec_info);
		cmd = cmd->next;
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == exec_info->pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		pid = waitpid(-1, &status, 0);
	}
	//kill()
}

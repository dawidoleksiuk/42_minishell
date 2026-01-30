/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/30 20:52:10 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	kill_process(t_exec_info *exec_info, char exit_code, void *content)
{
	if (content)
		free(content);
	free(exec_info->path);
	free(exec_info);
	exit(exit_code);
}

static char *check_path(t_exec_info *exec_info)
{
	char	*str;

	str =  NULL;
	if (exec_info->cmd->args[0][0] == '~' && exec_info->home_dir)
	{
		str = ft_strjoin(exec_info->home_dir, exec_info->cmd->args[0]);
		if (!str)
			kill_process(exec_info, 1, NULL);
		if (access(str, F_OK) == 1)
			return (free(str), NULL);
		if (access(str, X_OK) == 1)
			kill_process(exec_info, 126, str);
	}
	return (str);
}

static t_exec_info	*check_catalogs(t_exec_info *exec_info, char *path, char *f_name)
{
	if (!f_name)
		kill_process(exec_info, 1, NULL);
	exec_info->path = ft_strjoin(path, f_name);
	if (!exec_info->path)
		kill_process(exec_info, 1, f_name);
	if (access(exec_info->path, F_OK) == 0)
	{
		if (access(exec_info->path, X_OK) == 1)
		{
			free(exec_info->path);
			exec_info->path = NULL;
		}
	}
	else
	{
		free(exec_info->path);
		exec_info->path = NULL;
	}
	free(f_name);
	return (exec_info);
}

static void	do_your_job(t_exec_info *exec_info)
{
	size_t	i;

	i = 0;
	// if (check_for_built_ins(exec_info->data, exec_info->cmd))
	// 	kill_process(exec_info, 1, NULL);
	exec_info->path = check_path(exec_info);
	if (!exec_info->path)
	{
		while (exec_info->catalogs && exec_info->catalogs[i] && !exec_info->path)
		{
			exec_info->temp = exec_info->catalogs[i++];
			if (!exec_info->temp)
				kill_process(exec_info, 3, NULL);
			exec_info = check_catalogs(exec_info, exec_info->temp, ft_strjoin("/", exec_info->cmd->args[0]));
		}  
	}
	if (!exec_info->path)
		kill_process(exec_info, 127, NULL);
	execve(exec_info->path, exec_info->cmd->args, exec_info->envp);
	perror("execve() failed\n");
	kill_process(exec_info, 1, NULL);
}

t_exec_info	*give_birth(t_exec_info *exec_info, t_cmd *cmd)
{
	if (exec_info->error || pipe(exec_info->pipe_fd) == -1)
		return (exec_info->error += exec_info->error == 0, exec_info);
	exec_info->pid = fork();
	if (exec_info->pid == -1)
		return (exec_info->error = 1, exec_info);
	else if (exec_info->pid == 0)
	{
		exec_info = redir(exec_info, cmd->redirs);
		dup2(exec_info->in, 0);
		if (exec_info->redir_out)
			dup2(exec_info->out, 1);
		else
			dup2(exec_info->pipe_fd[1], 1);
		close(exec_info->pipe_fd[0]);
	}
	else
	{
		if (exec_info->in)
			close(exec_info->in);
		close(exec_info->pipe_fd[1]);
		exec_info->in = exec_info->pipe_fd[0];
	}
	return (exec_info);
}
// int	check_for_built_ins(t_data *data, t_cmd *cmd)
// {
// 	if (!strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
// 		ft_cd();
// 	else if (!strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
// 		ft_echo();
// 	else if (!strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
// 		ft_env();
// 	else if (!strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
// 		ft_exit();
// 	else if (!strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
// 		ft_export();
// 	else if (!strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
// 		ft_pwd();
// 	else if (!strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
// 		ft_unset();
// 	else
// 		return (0);
// 	return (1);
	
// }
void	executor(t_data *data, t_cmd *cmd_head, char *exit_code)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;

	cmd = cmd_head;
	// if (!cmd->next && check_for_built_ins(data, cmd))
	// 	return ;
	while (cmd)
	{
		data->exec_info->cmd = cmd;
		data->exec_info = give_birth(data->exec_info, cmd);
		if (data->exec_info->pid == 0)
			do_your_job(data->exec_info);
		cmd = cmd->next;
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->exec_info->pid)
		{
			if (WIFEXITED(status))
				*exit_code = WEXITSTATUS(status);
		}
		pid = waitpid(-1, &status, 0);
	}
	if (data->exec_info->pipe_fd[1])
		close(data->exec_info->pipe_fd[1]);
	//kill()
}


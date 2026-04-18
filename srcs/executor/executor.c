/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/18 11:34:15 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static char *check_path(t_exec_info *exec_info)
{
	char	*str;

	str =  NULL;
	if (ft_strchr(exec_info->cmd->args[0], '/'))
	{
		if (exec_info->cmd->args[0][0] == '~' && exec_info->envars->home_dir)
			str = ft_strjoin(exec_info->envars->home_dir, exec_info->cmd->args[0] + 1);
		else
			str = ft_strdup(exec_info->cmd->args[0]);
		if (!str)
				clean_exec(exec_info, "malloc failed\n", 1, NULL);
		if (access(str, F_OK) == 1)
			return (free(str), NULL);
		if (access(str, X_OK) == 1)
			clean_exec(exec_info, "access denied\n", 126, str);
	}
	return (str);
}

static t_exec_info	*check_catalogs(t_exec_info *exec_info, char *path, char *f_name)
{
	if (!f_name)
		clean_exec(exec_info, "malloc failed\n", 1, NULL);
	exec_info->path = ft_strjoin(path, f_name);
	if (!exec_info->path)
		clean_exec(exec_info, "malloc failed\n", 1, f_name);
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

int	check_for_built_ins(t_data *data, t_cmd *cmd)
{
	if (!cmd->args)
		return (0);
	if (!strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
		ft_cd(&data->exec_info->envars, cmd->args[1]);
 	else if (!strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
		ft_echo(data->exec_info->out, cmd->args + 1);
	else if (!strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
		ft_env(data->exec_info->envars->table, data->exec_info->out);
	else if (!strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		ft_exit(data, cmd->args);
	else if (!strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
		ft_export(data->exec_info, &data->exec_info->envars->table, cmd->args, data->exec_info->out);
	else if (!strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
		ft_pwd(&data->exec_info->envars);
	else if (!strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
		ft_unset(&data->exec_info->envars->table, cmd->args + 1);
	else
		return (0);
	return (1);
}

static void	do_your_job(t_data *data, t_exec_info *exec_info, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (check_for_built_ins(data, cmd))
		return (clean_exec(data->exec_info, NULL, 1, NULL));
	exec_info->path = check_path(exec_info);
	if (!exec_info->path)
	{
		while (exec_info->envars->catalogs && exec_info->envars->catalogs[i] && !exec_info->path)
		{
			exec_info->temp = exec_info->envars->catalogs[i++];
			if (!exec_info->temp)
				clean_exec(exec_info, "no catalogs were found\n", 1, NULL);
			exec_info = check_catalogs(exec_info, exec_info->temp, ft_strjoin("/", exec_info->cmd->args[0]));
		}  
	}
	if (!exec_info->path)
		clean_exec(exec_info, "command not found\n",127, NULL);
	execve(exec_info->path, exec_info->cmd->args, exec_info->envars->envp);
	clean_exec(exec_info, "execve() failed\n", 1, NULL);
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
	else if (exec_info->pid == 0)
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
	else
	{
		if (exec_info->in)
			close(exec_info->in);
		close(exec_info->pipe_fd[1]);
		exec_info->in = exec_info->pipe_fd[0];
	}
	return (exec_info);
}

void	execute(t_data *data, t_cmd *cmd)
{
	data->exec_info->cmd = cmd;
	data->exec_info = give_birth(data, data->exec_info, cmd);
	if (g_signum)
		clean_exec(data->exec_info, NULL, 0, NULL);
	if (data->exec_info->error)
		return ;
	if (data->exec_info->pid == 0)
		do_your_job(data, data->exec_info, cmd);
}

void	executor(t_data *data, t_cmd *cmd_head, unsigned char *exit_code)
{
	t_cmd	*cmd;
	
	data->exec_info->pipe_fd = ft_calloc(2, sizeof(int));
	if (!data->exec_info->pipe_fd)
		return (clean_exec(data->exec_info, "Malloc failed\n", 1, NULL));
	cmd = cmd_head;
	if (cmd && !cmd->next && !cmd->redirs && check_for_built_ins(data, cmd))
		return (clean_exec(data->exec_info, NULL, 0, NULL));
	while (cmd)
	{
		execute(data, cmd);
		cmd = cmd->next;
	}
	check_out_children(data->exec_info, exit_code);
	if (isatty(STDIN_FILENO))
		set_terminal_settings(data, 0);
	if (data->exec_info->pipe_fd[1])
		close(data->exec_info->pipe_fd[1]);
	clean_exec(data->exec_info, NULL, 0, NULL);
}

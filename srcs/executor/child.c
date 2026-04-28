/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:17:07 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/28 14:52:12 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "sys/stat.h"

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

static int	check_for_directory(char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

static char	*check_path(t_exec_info *exec_info, char **args)
{
	char	*str;

	str = NULL;
	if (args[0] && ft_strchr(args[0], '/'))
	{
		if (args[0][0] == '~' && exec_info->envars->home_dir)
			str = ft_strjoin(exec_info->envars->home_dir,
					exec_info->cmd->args[0] + 1);
		else
			str = ft_strdup(args[0]);
		if (!str)
			clean_exec(exec_info, "malloc failed\n", 1, NULL);
		if (check_for_directory(str))
				clean_exec(exec_info, "Is a directory\n", 126, str);
		if (access(str, F_OK) == -1)
			clean_exec(exec_info, "No such file or directory\n", 127, str);
		if (access(str, X_OK) == -1)
			clean_exec(exec_info, "Permission denied\n", 126, str);
	}
	return (str);
}

static t_exec_info	*check_catalogs(t_exec_info *exec_info,
					char *path, char *f_name)
{
	if (!f_name)
		clean_exec(exec_info, "malloc failed\n", 1, NULL);
	exec_info->path = ft_strjoin(path, f_name);
	if (!exec_info->path)
		clean_exec(exec_info, "malloc failed\n", 1, f_name);
	if (access(exec_info->path, F_OK) == 0)
	{
		if (access(exec_info->path, X_OK) == -1)
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

static char	**filtr_cmd(t_cmd *cmd)
{
	char	**args;
	char	**args_cpy;
	size_t	i;
	

	i = 0;
	while (cmd->args[i])
		i++;
	args = malloc((i + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	args_cpy = cmd->args;
	while (args_cpy[0])
	{
		if (ft_strlen(args_cpy[0]))
			args[i++] = args_cpy[0];
		args_cpy++;
	}
	args[i] = NULL;
	return (args);
}

void	do_your_job(t_data *data, t_exec_info *exec_info, t_cmd *cmd)
{
	size_t	i;
	i = 0;

	exec_info->args = filtr_cmd(cmd);
	if (!exec_info->args)
		return (clean_exec(exec_info, "malloc failed\n", 1, NULL));
	if (!exec_info->args[0])
		return (clean_exec(exec_info, "", 0, NULL));
	if (check_for_built_ins(data, cmd))
		return (clean_exec(data->exec_info, "", 0, NULL));
	exec_info->path = check_path(exec_info, exec_info->args);
	if (!exec_info->path)
	{
		while (exec_info->envars->catalogs
			&& exec_info->envars->catalogs[i] && !exec_info->path)
		{
			exec_info->temp = exec_info->envars->catalogs[i++];
			if (!exec_info->temp)
				clean_exec(exec_info, "no catalogs were found\n", 1, NULL);
			exec_info = check_catalogs(exec_info, exec_info->temp,
					ft_strjoin("/", exec_info->args[0]));
		}
	}
	if (!exec_info->path)
		clean_exec(exec_info, "command not found\n", 127, NULL);
	execve(exec_info->path, exec_info->cmd->args, exec_info->envars->envp);
	clean_exec(exec_info, "execve() failed\n", 1, NULL);
}

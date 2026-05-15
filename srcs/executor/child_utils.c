/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 07:06:42 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/15 20:35:44 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "sys/stat.h"

void	iter_catalogs(t_exec_info *exec_info)
{
	size_t	i;

	i = 0;
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

char	**filtr_cmd(t_cmd *cmd)
{
	char	**args;
	char	**args_cpy;
	size_t	i;

	i = 0;
	if (!cmd->args)
		return (cmd->args);
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

char	*check_path(t_exec_info *exec_info, char **args)
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

t_exec_info	*check_catalogs(t_exec_info *exec_info,
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

int	check_for_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

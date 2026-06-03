/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:51:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/06/03 06:50:29 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../hash_table/hash_table.h"

void	ft_exit(t_data *data, char **args)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		ft_printf("exit\n");
	if (!args[1])
		clean_exit(data, NULL, 0);
	if (!ft_aisll(args[1], &exit_code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_exit(data, NULL, 2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exec_info->error = 1;
	}
	else
		clean_exit(data, NULL, (unsigned char)exit_code);
}

void	ft_echo(int fd, char **args)
{
	char	flag;
	size_t	i;

	i = 0;
	flag = 0;
	if (!fd)
		fd = STDOUT_FILENO;
	if (args[0] && ft_strisequal(args[0], "-n", 0))
		flag = 1;
	while (args[flag + i])
	{
		ft_putstr_fd(args[flag + i], fd);
		if (args[flag + i + 1] && ft_strlen(args[flag + i]))
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
}

static char	*export_path(t_envar *envar, char *str)
{
	char	*path;

	if (str[0] == '~' && envar->home_dir)
		path = ft_strjoin(envar->home_dir, str + 1);
	else if (str[0] != '/')
	{
		path = ft_strjoin("/", str);
		if (!path)
			return (NULL);
		str = path;
		path = ft_strjoin(envar->curr_dir, str);
		free(str);
	}
	else
		path = ft_strdup(str);
	return (path);
}

int	ft_cd(t_data *data, char **args)
{
	char	*temp;
	char	*path;

	temp = args[0];
	if (!temp)
		return (0);
	if (args[1])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	path = export_path(data->exec_info->envars, temp);
	if (!path)
		return (1);
	if (chdir(path) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(args[0], 2),
			ft_putendl_fd(": No such file or directory", 2), free(path), 1);
	else
	{
		free(data->exec_info->envars->curr_dir);
		data->exec_info->envars->curr_dir = path;
		temp = ft_strjoin("PWD=", path);
		if (!temp)
			return (1);
		temp[ft_strlen(temp) - 1] = 0;
		data->table->set(&(data->table->table), temp);
		return (free(temp), 0);
	}
}

int	ft_pwd(t_envar **envar)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
		return (0);
	}
	else if (envar && *envar && (*envar)->curr_dir)
	{
		ft_printf("%s\n", (*envar)->curr_dir);
		return (0);
	}
	perror("pwd");
	return (1);
}

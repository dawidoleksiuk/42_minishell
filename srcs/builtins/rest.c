/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:51:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/15 19:56:21 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!fd)
		fd = STDOUT_FILENO;
	if (args[0] && ft_strisequal(args[0], "-n", 0))
		flag = 1;
	else
		flag = 0;
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

int	ft_cd(t_envar **envar, char **args)
{
	char	*temp;
	char	*path;

	path = args[0];
	if (!path)
		return (0);
	if (args[1])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (path[0] == '~' && (*envar)->home_dir)
		temp = ft_strjoin((*envar)->home_dir, path + 1);
	else if (path[0] != '/')
	{
		temp = ft_strjoin("/", path);
		if (!temp)
			return (1);
		path = temp;
		temp = ft_strjoin((*envar)->curr_dir, path);
		free(path);
	}
	else
		temp = ft_strdup(path);
	if (!temp)
		return (1);
	if (chdir(temp) == -1)
		return (perror("cd"), free(temp), 1);
	else
		return (free((*envar)->curr_dir), (*envar)->curr_dir = temp, 0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:51:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/03/05 05:27:43 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	display_table(t_list **table, char *prefix, char null_values, char sorted)
{
	size_t	i;
	t_list	*temp;
	t_list	*node;

	node = NULL;
	i = 0;
	while (i < 63)
	{
		if (sorted)
		{
			if (node_sort(&node, table[i++]))
				return (1);
		}
		else
			node = table[i++];
		while (node)
		{
			if (!node->value && null_values)
				ft_printf("%s%s=\"\"\n", prefix, node->key);
			else
				ft_printf("%s%s=\"%s\"\n", prefix, node->key, node->value);
			if (sorted)
			{
				temp = node;
				node = node->next;
				free(temp);
			}
			else
				node = node->next;
		}
	}
	return (0);
}

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
		clean_exit(data, NULL, 255);
	}
	if (args[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
		clean_exit(data, NULL, (unsigned char)exit_code);
}

void	ft_env(t_list **table)
{
	display_table(table, "", 0, 0);
}

void	ft_unset(t_list **table, char **args)
{
	ssize_t	i;

	if (!args[1])
		return ;
	i = table_get_i(args[1][0]);
	if (i == -1)
		return ;
	table[i] = table_del(table[i], args[1]);
}

void	ft_export(t_exec_info *exec, t_list **table, char **args)
{
	ssize_t	i;
	t_list	*node;
	char	*key;
	char	*value;

	if (!args[1])
	{
		display_table(table, "declare -x ", 1, 1);
		return ;
	}
	i = table_get_i(args[1][0]);
	if (i < 0)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	if (table_sep_string(args[1], &key, &value))
		return (clean_exec(exec, "malloc failed\n", 1, key));
	node = table_find_node(table, key);
	if (!node)
	{
		if (table_add(table, key, value))
			return (clean_exec(exec, "malloc failed\n", 1, key));
	}
	else
		node->value = value;
}

void	ft_echo(int	fd, char **args)
{
	char	flag;
	size_t	i;

	i = 0;
	if (args[0] && ft_strncmp(args[0], "-n", 3) == 0)
		flag = 1;
	else
		flag = 0;
	while (args[flag + i])
	{
		ft_putstr_fd(args[flag + i++], fd);
		if (args[flag + i])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}

int	ft_cd(t_envar **envar, char *path)
{
	char	*temp;

	if (path[0] == '~' && (*envar)->home_dir)
		temp = ft_strjoin((*envar)->home_dir, path + 1);
	else
	{
		temp = ft_strjoin("/", path);
		if (!temp)
			return (1);
		path = temp;
		temp = ft_strjoin((*envar)->curr_dir, path);
	}
	if (!temp)
			return (1);
	if (chdir(temp) == -1)
		perror("cd");
	else
	{
		free((*envar)->curr_dir);
		(*envar)->curr_dir = temp;
		return (0);
	}
	return (1);
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

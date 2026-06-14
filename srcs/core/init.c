/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:35:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/06/14 12:09:06 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_envp(t_data *data, char **envp)
{
	char	*str;

	data->exec_info->envars = ft_calloc(1, sizeof(t_envar));
	if (!data->exec_info->envars)
		return (1);
	data->exec_info->envars->envp = envp;
	data->exec_info->envars->home_dir = getenv("HOME");
	str = getenv("PWD");
	data->exec_info->envars->curr_dir = ft_strdup(str);
	if (!data->exec_info->envars->curr_dir || !data->exec_info->envars->envp)
		return (1);
	return (0);
}

int	init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	if (isatty(STDIN_FILENO) && init_signals(data) == 1)
		return (1);
	data->exec_info = ft_calloc(1, sizeof(t_exec_info));
	if (!data->exec_info)
		return (1);
	data->exec_info->out = 1;
	data->table = table_init(envp);
	if (!data->table)
		return (1);
	if (!data->exec_info || get_envp(data, envp))
		return (1);
	data->exec_info->data = data;
	return (0);
}

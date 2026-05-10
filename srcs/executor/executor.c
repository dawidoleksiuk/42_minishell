/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 14:44:23 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	check_for_built_ins(t_data *data, t_cmd *cmd)
{
	char	**args;

	args = cmd->args;
	while (args && args[0] && !ft_strlen(args[0]))
		args = args + 1;
	if (!args || !args[0])
		return (0);
	if (ft_strisequal(args[0], "cd", 2))
		data->exec_info->error = ft_cd(&data->exec_info->envars, args + 1);
	else if (ft_strisequal(args[0], "echo", 4))
		ft_echo(data->exec_info->out, args + 1);
	else if (ft_strisequal(args[0], "env", 3))
		ft_env(data->exec_info->envars->table, data->exec_info->out);
	else if (ft_strisequal(args[0], "exit", 4))
		ft_exit(data, args);
	else if (ft_strisequal(args[0], "export", 6))
		ft_export(data->exec_info, &data->exec_info->envars->table,
			args, data->exec_info->out);
	else if (ft_strisequal(args[0], "pwd", 3))
		ft_pwd(&data->exec_info->envars);
	else if (ft_strisequal(args[0], "unset", 5))
		ft_unset(&data->exec_info->envars->table, args + 1);
	else
		return (0);
	return (1);
}

void	execute(t_data *data, t_cmd *cmd)
{
	data->exec_info->cmd = cmd;
	data->exec_info = give_birth(data, data->exec_info, cmd);
	if (g_signum)
		clean_exec(data->exec_info, NULL, 0, NULL);
	if (data->exec_info->error)
	{
		data->exit_code = data->exec_info->error;
		return ;
	}
	if (data->exec_info->pid == IS_CHILD)
		do_your_job(data, data->exec_info, cmd);
}

void	executor(t_data *data, t_cmd *cmd_head)
{
	t_cmd	*cmd;

	data->exec_info->pipe_fd = ft_calloc(2, sizeof(int));
	if (!data->exec_info->pipe_fd)
		return (clean_exec(data->exec_info, "Malloc failed\n", 1, NULL));
	cmd = cmd_head;
	if (cmd && !cmd->next && !cmd->redirs && check_for_built_ins(data, cmd))
		return (data->exit_code = data->exec_info->error,
			clean_exec(data->exec_info, NULL, 0, NULL));
	while (cmd)
	{
		execute(data, cmd);
		cmd = cmd->next;
		data->exec_info->out = 1;
	}
	check_out_children(data->exec_info, &data->exit_code);
	if (isatty(STDIN_FILENO))
		set_terminal_settings(data, 0);
	if (data->exec_info->pipe_fd[1])
		close(data->exec_info->pipe_fd[1]);
	clean_exec(data->exec_info, NULL, 0, NULL);
}

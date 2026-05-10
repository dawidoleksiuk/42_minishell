/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:09 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 12:53:55 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	clean_exec(t_exec_info *exec_info,
			char *msg, int exit_code, void *bonus)
{
	if (bonus)
		free(bonus);
	if (exec_info->pipe_fd)
		free(exec_info->pipe_fd);
	if (exec_info->path)
		free(exec_info->path);
	exec_info->pipe_fd = NULL;
	exec_info->path = NULL;
	exec_info->temp = NULL;
	exec_info->in = 0;
	exec_info->out = 0;
	exec_info->error = 0;
	if (exec_info->args)
	{
		free(exec_info->args);
		exec_info->args = NULL;
	}
	if (msg && ft_strlen(msg))
	{
		ft_putstr_fd(exec_info->cmd->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (msg || exit_code)
		clean_exit(exec_info->data, NULL, exit_code);
}

void	clean_envars(t_envar *envars)
{
	size_t	i;

	if (envars->curr_dir)
		free(envars->curr_dir);
	if (envars->catalogs)
	{
		i = 0;
		while (envars->catalogs[i])
			free(envars->catalogs[i++]);
		free(envars->catalogs);
		envars->catalogs = NULL;
	}
	free(envars);
}

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
		if (disable_echoctl() != 0)
			return (clean_exec(data->exec_info,
					"disable_echoctl failed\n", 1, NULL));
	if (data->exec_info->pipe_fd[1])
		close(data->exec_info->pipe_fd[1]);
	clean_exec(data->exec_info, NULL, 0, NULL);
}

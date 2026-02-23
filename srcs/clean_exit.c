/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/02/23 18:05:59 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char	**args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (data->cmd_head)
	{
		cmd = data->cmd_head;
		while (cmd)
		{
			if (cmd->args)
				free_args(cmd->args);
			temp = cmd;
			cmd = cmd->next;
			free(temp);
		}
		data->cmd_head = NULL;
	}
}

void	free_tokens(t_data *data)
{
	t_token	*token;
	t_token	*temp;

	if (data->token_head)
	{
		token = data->token_head;
		while (token)
		{
			if (token->content)
			{
				free(token->content);
				token->content = NULL;
			}
			temp = token;
			token = token->next;
			free(temp);
		}
		data->token_head = NULL;
	}
}

void	clean_exec(t_exec_info *exec_info, char *msg, int exit_code, void *bonus)
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
	if (exit_code)
	{
		if (msg)
		{
			ft_putstr_fd(exec_info->cmd->args[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(msg, 2);
		}
		clean_exit(exec_info->data, NULL, exit_code);
	}
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

void	clean_exit(t_data *data, char *msg, int exit_code)
{	
	if (data)
	{
		if (msg)
		{
			ft_putstr_fd(msg, 2);
			ft_putstr_fd("\n", 2);
		}
		if (data->error_msg)
			free(data->error_msg);
		rl_clear_history();
		if (data->line)
			free (data->line);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p_save))
			perror("error in tcsetattr");
		free_tokens(data);
		free_cmd(data);
		if (data->exec_info->envars->table)
			table_clear(data->exec_info->envars->table);
		if (data->exec_info && data->exec_info->envars)
			clean_envars(data->exec_info->envars);
		if (data->exec_info && data->exec_info->pipe_fd)
			free(data->exec_info->pipe_fd);
		if (data->exec_info)
			free(data->exec_info);
	}
	exit (exit_code);
}

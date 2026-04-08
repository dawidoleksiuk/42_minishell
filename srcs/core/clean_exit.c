/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/04/08 12:29:13 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args_node(t_cmd *node)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (node->args && node->args[i])
	{
		free(node->args[i]);
		i++;
	}
	free(node->args);
	redir = node->redirs;
	while (redir)
	{
		node->redirs = redir->next;
		free(redir->filename);
		free(redir);
		redir = node->redirs;
	}
	free(node);
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

			temp = cmd;
			cmd = cmd->next;
			free_args_node(temp);
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
	if (msg && ft_strlen(msg))
	{
		ft_putstr_fd(exec_info->cmd->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		clean_exit(exec_info->data, NULL, exit_code);
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

void	put_msg(char *msg)
{
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	clean_exit(t_data *data, char *msg, int exit_code)
{	
	if (data)
	{
		put_msg(msg);
		if (data->error_msg)
			free(data->error_msg);
		rl_clear_history();
		if (data->prev_exit)
			free(data->prev_exit);
		if (data->line)
			free(data->line);
		if(isatty(STDIN_FILENO) && tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p_save) < 0)
			perror("minishell: tcsetattr error");
		if (data->token_head)
			free_tokens(data);
		if (data->cmd_head)
			free_cmd(data);
		if (data->exec_info->envars->table)
			data->exec_info->envars->table->clear(data->exec_info->envars->table);
		if (data->exec_info && data->exec_info->envars)
			clean_envars(data->exec_info->envars);
		if (data->exec_info && data->exec_info->pipe_fd)
			free(data->exec_info->pipe_fd);
		if (data->exec_info)
			free(data->exec_info);
	}
	// printf("exit");
	exit(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/10 14:48:39 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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
	if (!data)
		exit(exit_code);
	put_msg(msg);
	if (data->error_msg)
		free(data->error_msg);
	rl_clear_history();
	if (data->prev_exit)
		free(data->prev_exit);
	if (data->line)
		free(data->line);
	if (isatty(STDIN_FILENO)
		&& tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p_save) < 0)
		perror("minishell: tcsetattr error");
	if (data->token_head)
		free_tokens(data);
	if (data->cmd_head)
		free_cmd(data);
	if (data->exec_info)
		clean_exit_executor(data->exec_info);
	exit(exit_code);
}

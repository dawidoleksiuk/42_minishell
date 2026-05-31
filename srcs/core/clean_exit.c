/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/31 12:54:06 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	free_redirs(t_redir	*redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp->filename);
		free(temp);
	}
}

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args && args[i])
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
			temp = cmd;
			cmd = cmd->next;
			free_args(temp->args);
			free_redirs(temp->redirs);
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

void	clean_exit(t_data *data, char *msg, int exit_code)
{
	if (!data)
		exit(exit_code);
	if (msg)
		ft_putendl_fd(msg, 2);
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

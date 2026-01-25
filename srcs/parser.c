/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:38:03 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:56 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_cmd	*new_cmd_node(t_data *data, t_cmd *cmd)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		clean_exit(data, "Malloc failed");
	node->args = NULL;
	node->redirs = NULL;
	node->next = NULL;
	if (cmd != NULL)
		cmd->next = node;
	else
		data->cmd_head = node;
	// (*cmd) = node;
	return (node);
}
int	copy_args(t_data *data, t_token *token, t_cmd *cmd)
{
	int		i;
	char	**args;

	i = 0;
	args = cmd->args;
	while (args && args[i])
		i++;
	while (token && token->type == WORD)
	{
		i++;
		token = token->next;
	}
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		clean_exit(data, "Malloc failed");
	i = 0;
	while (args && args[i])
	{
		cmd->args[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	return (i);
}

t_token	*add_cmd(t_data *data, t_token *token, t_cmd *cmd)
{
	(void) data;
	int		i;

	i = copy_args(data, token, cmd);
	while (token && token->type == WORD)
	{
		cmd->args[i] = ft_strdup(token->content);
		i++;
		token = token->next;
	}
	cmd->args[i] = NULL;
	return (token);
}

t_redir	*new_redir_node(t_data *data, t_cmd *cmd)
{
	t_redir	*node;
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir && redir->next)
		redir = redir->next;
	node = malloc(sizeof(t_redir));
	if (!node)
		clean_exit(data, "Malloc failed");
	node->next = NULL;
	node->filename = NULL;
	node->type = 0;
	if (cmd->redirs != NULL)
		redir->next = node;
	else
		cmd->redirs = node;
	return (node);
}

t_token	*add_redir(t_data *data, t_token *token, t_cmd *cmd)
{
	t_redir	*current_redir;

	current_redir = new_redir_node(data, cmd);
	current_redir->type = token->type;
	token = token->next;
	current_redir->filename = ft_strdup(token->content);
	token = token->next;
	return (token);
}

void	parser(t_data *data)
{
	t_token	*token;
	t_cmd	*current_cmd;
	
	token = data->token_head;
	current_cmd = data->cmd_head;
	while (token)
	{
		if ((token && token->type == PIPE) || current_cmd == NULL)
		{
			current_cmd = new_cmd_node(data, current_cmd);
			if (token->type == PIPE)
				token = token->next;
		}
		if (token && token->type == WORD)
			token = add_cmd(data, token, current_cmd);
		if (token && token->type != WORD && token->type != PIPE)
			token = add_redir(data, token, current_cmd);
	}
}

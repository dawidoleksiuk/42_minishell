/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:38:03 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/31 14:05:49 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(t_data *data, t_cmd *cmd)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		clean_exit(data, "Malloc failed", 0);
	node->args = NULL;
	node->redirs = NULL;
	node->next = NULL;
	if (cmd != NULL)
		cmd->next = node;
	else
		data->cmd_head = node;
	return (node);
}

/*
Reallocates the cmd argument array to save new token arguments, 
saving the existing arguments.
*/

int	realloc_args(t_data *data, t_token *token, t_cmd *cmd)
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
	cmd->args = malloc((i + 1) * sizeof(char *));
	if (!cmd->args)
		return (free_args(args), clean_exit(data, "Malloc failed", 0), 0);
	i = 0;
	while (args && args[i])
	{
		cmd->args[i] = args[i];
		i++;
	}
	return (free(args), i);
}

t_token	*add_args(t_data *data, t_token *token, t_cmd *cmd)
{
	int		i;

	i = realloc_args(data, token, cmd);
	while (token && token->type == WORD)
	{
		if (token->content[0])
		{
			cmd->args[i] = ft_strdup(token->content);
			if (!cmd->args[i])
			{
				cmd->args[i] = NULL;
				clean_exit(data, "Malloc failed", 0);
			}
			i++;
		}
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
		clean_exit(data, "Malloc failed", 0);
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
	if (!current_redir->filename)
		clean_exit(data, "Malloc failed", 0);
	token = token->next;
	return (token);
}

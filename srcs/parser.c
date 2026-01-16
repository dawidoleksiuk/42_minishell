/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:38:03 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/16 21:49:03 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	new_redir_node(t_data *data)
// {

// }

t_cmd	*new_cmd_node(t_data *data, t_cmd **cmd)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		clean_exit(data, "Malloc failed");
	node->args = NULL;
	node->redirs = NULL;
	node->next = NULL;
	if (*cmd != NULL)
		(*cmd)->next = node;
	else
	{
		data->cmd_head = node;
	}
	// (*cmd) = node;
	return (node);
}

t_token	*add_cmd(t_data *data, t_token *token, t_cmd **cmd)
{
	(void) data;
	t_token	*token_copy;
	int	counter;
	int	i;

	token_copy = token;
	counter = 0;
	i = 0;
	while (token_copy && token_copy->type == WORD)
	{
		counter++;
		token_copy = token_copy->next;
	}
	(*cmd)->args = malloc(sizeof(char *) * (counter + 1));
	while (token && token->type == WORD)
	{
		(*cmd)->args[i] = ft_strdup(token->content);
		// printf("%d\n", i);
		i++;
		token = token->next;
	}
	(*cmd)->args[i] = NULL;
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
			current_cmd = new_cmd_node(data, &current_cmd);
			if (token->type == PIPE)
				token = token->next;
		}
		if (token && token->type == WORD)
			token = add_cmd(data, token, &current_cmd);
		// else if (token->type != WORD && token->type != PIPE)
		// 	add_redir(data, token, cmd);
	}
}

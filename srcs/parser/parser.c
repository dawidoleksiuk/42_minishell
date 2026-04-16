/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:38:03 by doleksiu          #+#    #+#             */
/*   Updated: 2026/04/16 20:18:02 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

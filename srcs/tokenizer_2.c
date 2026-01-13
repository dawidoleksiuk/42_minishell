/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:21:51 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/13 18:53:22 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign_token_type(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		if (ft_strncmp(token->content, "|", 1) == 0)
			token->type = PIPE;
		else if (ft_strncmp(token->content, "<<", 2) == 0)
			token->type = HEREDOC;
		else if (ft_strncmp(token->content, ">>", 2) == 0)
			token->type = APPEND;
		else if (ft_strncmp(token->content, "<", 1) == 0)
			token->type = REDIR_IN;
		else if (ft_strncmp(token->content, ">", 1) == 0)
			token->type = REDIR_OUT;
		else
			token->type = WORD;
		token = token->next;
	}
}

void	check_syntax(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		if ((token->type == PIPE && token->next && token->next->type == PIPE) 
			|| ((token->type != WORD && token->type != PIPE) 
			&& ((token->next && token->next->type != WORD))))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			data->error_msg = ft_strjoin(token->next->content, "'");
			clean_exit(data, data->error_msg);
		}
		else if ((token->type == PIPE && token == data->token_head))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			data->error_msg = ft_strjoin(token->content, "'");
			clean_exit(data, data->error_msg);
		}
		else if (token->type != WORD && token->next == NULL)
		{
			clean_exit(data, "minishell: syntax error near unexpected token `newline'");
		}
		token = token->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:21:51 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/13 16:24:05 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_separator(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '\t')
		return (1);
	return (0);
}

int	check_syntax(t_data *data)
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
			ft_putstr_fd(token->next->content, 2);
			return (ft_putendl_fd("'", 2), 1);
		}
		else if ((token->type == PIPE && token == data->token_head))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->content, 2);
			return (ft_putendl_fd("'", 2), 1);
		}
		else if (token->type != WORD && token->next == NULL)
			return (ft_putendl_fd("minishell: syntax error"
					" near unexpected token `newline'", 2), 1);
		token = token->next;
	}
	return (0);
}

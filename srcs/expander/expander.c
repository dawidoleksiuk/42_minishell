/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:22:06 by doleksiu          #+#    #+#             */
/*   Updated: 2026/06/06 12:01:42 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This function takes char *content 
and appends a specified number of chars (substr_len) to res
*/

void	append_substr(t_data *data, char *content, char **res, int substr_len)
{
	char	*res1;
	char	*res2;

	res1 = NULL;
	res2 = NULL;
	res1 = ft_substr(content, 0, substr_len);
	if (!res1)
	{
		free(*res);
		clean_exit(data, "Malloc failed", 0);
	}
	res2 = ft_strjoin(*res, res1);
	free(*res);
	free(res1);
	if (!res2)
		clean_exit(data, "Malloc failed", 0);
	*res = res2;
}

void	process_char(t_data *data, t_exp_data *exp, t_token	*t, char **res)
{
	if (exp->status == DEFAULT && exp->c == '\'')
	{
		t->was_quoted = 1;
		exp->status = IN_SINGLE;
	}
	else if (exp->status == DEFAULT && exp->c == '\"')
	{
		t->was_quoted = 1;
		exp->status = IN_DOUBLE;
	}
	else if ((exp->status == IN_SINGLE && exp->c == '\'')
		|| (exp->status == IN_DOUBLE && exp->c == '\"'))
		exp->status = DEFAULT;
	if ((exp->status != IN_SINGLE) && exp->c == '$')
	{
		append_substr(data, t->content + exp->start, res, exp->i - exp->start);
		exp->start = exp->i;
		append_dollar(data, exp, t->content, res);
	}
	if ((exp->status != IN_SINGLE && exp->c == '\"')
		|| (exp->status != IN_DOUBLE && exp->c == '\''))
	{
		append_substr(data, t->content + exp->start, res, exp->i - exp->start);
		exp->start = exp->i + 1;
	}
}

/*
iterates through each token content char and:
- checks quotes and updates quote status if found one
- inserts dollar value if found '$', and not IN_SINGLE quote

res is the result of the content after processing
*/

char	*process_token_content(t_data *data, t_token *token)
{
	t_exp_data	exp;
	char		*res;

	exp = data->exp_data;
	res = NULL;
	while (token->content[exp.i])
	{
		exp.c = (token->content[exp.i]);
		process_char(data, &exp, token, &res);
		exp.i++;
	}
	append_substr(data, token->content + exp.start, &res, exp.i - exp.start);
	return (res);
}

void	expander(t_data *data)
{
	t_token	*token;
	char	*res;

	token = data->token_head;
	while (token)
	{
		res = process_token_content(data, token);
		if (res)
		{
			free(token->content);
			token->content = res;
		}
		token = token->next;
	}
}

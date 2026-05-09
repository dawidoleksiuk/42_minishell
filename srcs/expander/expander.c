/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:22:06 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/09 23:13:01 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(t_data *data, char *content, char **res, int pre_quote_len)
{
	char	*res1;
	char	*res2;

	(void)data;
	res1 = NULL;
	res2 = NULL;
	res1 = ft_substr(content, 0, pre_quote_len);
	res2 = ft_strjoin(*res, res1);
	if (!res1 || !res2)
		clean_exit(data, "Malloc failed", 0);
	free(*res);
	free(res1);
	*res = res2;
}

void	process_char(t_data *data, t_exp_data *exp, char *content, char **res)
{
	if (exp->status == DEFAULT && exp->c == '\'')
		exp->status = IN_SINGLE;
	else if (exp->status == DEFAULT && exp->c == '\"')
		exp->status = IN_DOUBLE;
	else if (exp->status == IN_SINGLE && exp->c == '\'')
		exp->status = DEFAULT;
	else if (exp->status == IN_DOUBLE && exp->c == '\"')
		exp->status = DEFAULT;
	if ((exp->status != IN_SINGLE) && exp->c == '$')
	{
		remove_quote(data, content + exp->start, res, exp->i - exp->start);
		exp->start = exp->i;
		insert_dollar(data, exp, content, res);
	}
	if ((exp->status != IN_SINGLE && exp->c == '\"')
		|| (exp->status != IN_DOUBLE && exp->c == '\''))
	{
		remove_quote(data, content + exp->start, res, exp->i - exp->start);
		exp->start = exp->i + 1;
	}
}

/*
iterates through each token content char and:
- checks quotes and updates quote status if found one
- inserts dollar value if found '$', and not IN_SINGLE quote


res is a result of the 

*/

char	*process_token_content(t_data *data, char *content)
{
	t_exp_data	exp;
	char		*res;

	exp = data->exp_data;
	res = NULL;
	while (content[exp.i])
	{
		exp.c = (content[exp.i]);
		process_char(data, &exp, content, &res);
		exp.i++;
	}
	remove_quote(data, content + exp.start, &res, exp.i - exp.start);
	return (res);
}

void	expander(t_data *data)
{
	t_token	*token;
	char	*res;

	token = data->token_head;
	while (token)
	{
		res = process_token_content(data, token->content);
		if (res)
		{
			free(token->content);
			token->content = res;
		}
		token = token->next;
	}
}

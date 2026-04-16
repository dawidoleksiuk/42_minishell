/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:22:06 by doleksiu          #+#    #+#             */
/*   Updated: 2026/04/16 20:10:26 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(t_data *data, char **res, char *content, int len)
{
	char	*res1;
	char	*res2;

	(void)data;
	res1 = NULL;
	res2 = NULL;
	res1 = ft_substr(content, 0, len);
	res2 = ft_strjoin(*res, res1);
	if (!res1 || !res2)
		clean_exit(data, "Malloc failed", 0);
	free(*res);
	free(res1);
	*res = res2;
}

char	*process_char(t_data *data, t_exp_data *exp, char **content, char *res)
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
		insert_dollar_val(data, exp, content);
	if ((exp->status != IN_SINGLE && exp->c == '\"')
		|| (exp->status != IN_DOUBLE && exp->c == '\''))
	{
		remove_quote(data, &res, *content + exp->start, exp->i - exp->start);
		exp->start = exp->i + 1;
	}
	return (res);
}

char	*process_token_content(t_data *data, char **content)
{
	t_exp_data	exp;
	char		*res;

	exp = data->exp_data;
	res = NULL;
	while ((*content)[exp.i])
	{
		exp.c = (*content)[exp.i];
		res = process_char(data, &exp, content, res);
		exp.i++;
	}
	// remove_quote(data, &res, *content + exp.start, exp.i - exp.start);
	if (res)
	{
		free(*content);
		*content = res;
	}
	return (res);
}

void	expand_tokens(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		process_token_content(data, &token->content);
		token = token->next;
	}
}

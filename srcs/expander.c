/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:25 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/27 18:52:31 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	env_handler(char *arg)
// {

// }

char	*remove_quote(t_data *data, char *temp, char *arg, int len)
{
	(void)data;
	char	*temp1;
	char	*temp2;
	temp1 = NULL;
	temp2 = NULL;
	temp1 = ft_substr(arg, 0, len);
	temp2 = ft_strjoin(temp, temp1);
	free(temp);
	free(temp1);
	return (temp2);
}

char	*expand_text_loop(t_data *data, t_exp_data	*ed, char *arg, char *temp)
{
	if (ed->status == DEFAULT)
	{
		if (arg[ed->i] == '\'')
			ed->status = IN_SINGLE;
		else if (arg[ed->i] == '\"')
			ed->status = IN_DOUBLE;
		// if ((ed->i > ed->start) && (arg[ed->i] == '\'' || arg[ed->i] == '\"'))
		// 	temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
	}
	else if (ed->status == IN_SINGLE && arg[ed->i] == '\'')
	{
		// temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
		ed->status = DEFAULT;
	}
	else if (ed->status == IN_DOUBLE && arg[ed->i] == '\"')
	{
		// temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
		ed->status = DEFAULT;
	}
	if ((ed->status == DEFAULT && (arg[ed->i] == '\'' || arg[ed->i] == '\"'))
		|| (ed->status == IN_SINGLE && arg[ed->i] == '\'')
		|| (ed->status == IN_DOUBLE && arg[ed->i] == '\"'))
		temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
	return (temp);
}

char	*expand_text(t_data *data, char *arg)
{
	char		*temp;
	t_exp_data	ed;

	ed = data->exp_data;
	ed.i = 0;
	ed.status = DEFAULT;
	ed.start = 0;
	temp = NULL;
	while (arg[ed.i])
	{
		temp = expand_text_loop(data, &ed, arg, temp);
		if (((ed.status == IN_DOUBLE || ed.status == DEFAULT)
				&& arg[ed.i] == '\"') || ((ed.status == IN_SINGLE
					|| ed.status == DEFAULT) && arg[ed.i] == '\''))
			ed.start = (ed.i) + 1;
		(ed.i)++;
	}
	temp = remove_quote(data, temp, arg + ed.start, ed.i - ed.start);
	if (temp)
	{
		free(arg);
		arg = temp;
	}
	return (temp);
}

void	expander(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		token->content = expand_text(data, token->content);
		token = token->next;
	}
}

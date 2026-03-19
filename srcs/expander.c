/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:25 by doleksiu          #+#    #+#             */
/*   Updated: 2026/03/19 21:24:09 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dolar_insert(char *variable, int *i, char **arg, int dolar_len)
{
	char	*before_dolar;
	char	*after_dolar;
	char	*temp;
	char	*str;
	
	before_dolar = NULL;
	after_dolar = NULL;
	temp = NULL;
	str = NULL;
	before_dolar = ft_substr(*arg, 0, *i);
	if (ft_strlen(*arg) > (size_t)(*i + dolar_len))
		after_dolar = ft_substr(*arg, *i + dolar_len, ft_strlen(*arg) - (*i + dolar_len));
	str = ft_strjoin(before_dolar, variable);
	free(before_dolar);
	if (after_dolar)
	{
		temp = ft_strjoin(str, after_dolar);
		free (str);
		free (after_dolar);
		str = temp;
	}
	*i = *i + ft_strlen(variable);
	free (*arg);
	*arg = str;
}


void	dolar_handler(t_data *data, int *i, char **arg)
{
	char *key;
	char *value;
	int	j;

	key = NULL;
	value = NULL;
	j = *i + 1;
	if ((*arg)[*i + 1] == '?')
	{
		value = ft_itoa(data->exit_code);
		dolar_insert(value, i, arg, 2);
	}
	else if (ft_isalnum((*arg)[j]) || (*arg)[j] == '_')
	{
		while ((*arg)[j])
			j++;
		key = ft_substr(*arg, *i + 1, j - (*i + 1));
		value = table_find_value(data->exec_info->envars->table, key);
		if (value)
			value = ft_strdup(value);
		else
			value = ft_strdup("");
		dolar_insert(value, i, arg, j - *i);
	}
	if (key)
		free (key);
	if (value)
		free (value);
}

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

char	*expand_text_loop(t_data *data, t_exp_data	*ed, char **arg, char *temp)
{
	if (ed->status == DEFAULT)
	{
		if ((*arg)[ed->i] == '\'')
			ed->status = IN_SINGLE;
		else if ((*arg)[ed->i] == '\"')
			ed->status = IN_DOUBLE;
		// if ((ed->i > ed->start) && (arg[ed->i] == '\'' || arg[ed->i] == '\"'))
		// 	temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
	}
	else if (ed->status == IN_SINGLE && (*arg)[ed->i] == '\'')
	{
		// temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
		ed->status = DEFAULT;
	}
	else if (ed->status == IN_DOUBLE && (*arg)[ed->i] == '\"')
	{
		// temp = remove_quote(data, temp, arg + ed->start, ed->i - ed->start);
		ed->status = DEFAULT;
	}
	if ((ed->status == IN_DOUBLE || ed->status == DEFAULT) && (*arg)[ed->i] == '$')
	{
		dolar_handler(data, &ed->i, arg);
	}
	if ((ed->status == DEFAULT && ((*arg)[ed->i] == '\'' || (*arg)[ed->i] == '\"'))
		|| (ed->status == IN_SINGLE && (*arg)[ed->i] == '\'')
		|| (ed->status == IN_DOUBLE && (*arg)[ed->i] == '\"'))
		temp = remove_quote(data, temp, *arg + ed->start, ed->i - ed->start);
	return (temp);
}

char	*expand_text(t_data *data, char **arg)
{
	char		*temp;
	t_exp_data	ed;

	ed = data->exp_data;
	ed.i = 0;
	ed.status = DEFAULT;
	ed.start = 0;
	temp = NULL;
	while ((*arg)[ed.i])
	{
		temp = expand_text_loop(data, &ed, arg, temp);
		if (((ed.status == IN_DOUBLE || ed.status == DEFAULT)
				&& (*arg)[ed.i] == '\"') || ((ed.status == IN_SINGLE
					|| ed.status == DEFAULT) && (*arg)[ed.i] == '\''))
			ed.start = (ed.i) + 1;
		if ((*arg)[ed.i] != '\0')
			(ed.i)++;
	}
	temp = remove_quote(data, temp, *arg + ed.start, ed.i - ed.start);
	if (temp)
	{
		free(*arg);
		*arg = temp;
	}
	return (temp);
}

void	expander(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		expand_text(data, &token->content);
		token = token->next;
	}
}

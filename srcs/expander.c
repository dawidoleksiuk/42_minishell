/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:25 by doleksiu          #+#    #+#             */
/*   Updated: 2026/02/22 18:31:07 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void dolar_insert(char *variable, int *i, char **arg, int dolar_len)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	
	temp1 = NULL;
	temp2 = NULL;
	temp3 = NULL;
	temp1 = ft_substr(*arg, 0, *i);
	if (ft_strlen(*arg) > (size_t)(*i + dolar_len))
		temp2 = ft_substr(*arg, *i + dolar_len, ft_strlen(*arg) - (*i + dolar_len));
	*i = *i + ft_strlen(variable);
	temp3 = ft_strjoin(temp1, variable);
	free (temp1);
	if (temp2)
	{
		temp1 = ft_strjoin(temp3, temp2);
		free (temp2);
		free (temp3);
		temp3 = temp1;
	}
	free (*arg);
	*arg = temp3;
}


void	dolar_handler(t_data *data, int *i, char **arg)
{
	char *temp1;
	char *temp2;
	int	j;

	temp1 = NULL;
	temp2 = NULL;
	j = *i;
	if ((*arg)[*i + 1] == '?')
	{
		temp1 = ft_itoa(data->exit_code);
		dolar_insert(temp1, i, arg, 2);
	}
	else
	{
		while ((*arg)[j] != ' ')
			j++;
		temp1 = ft_substr(*arg, *i + 1, j - *i);
		temp2 = ft_strdup(table_find_value(data->exec_info->envars->table, temp1));
		dolar_insert(temp2, i, arg, j - *i);
	}
	free(temp1);
	free(temp2);
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
		(ed.i)++;
	}
	temp = remove_quote(data, temp, *arg + ed.start, ed.i - ed.start);
	if (temp)
	{
		// free(*arg);
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

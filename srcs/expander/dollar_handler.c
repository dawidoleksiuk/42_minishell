/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:22:06 by doleksiu          #+#    #+#             */
/*   Updated: 2026/06/06 12:10:24 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_value(t_data *data, char **res, char *value)
{
	char	*temp;

	if (ft_strlen(value))
	{
		temp = ft_strjoin(*res, value);
		if (!temp)
		{
			free(*res);
			clean_exit(data, "Malloc failed", 0);
		}
		free(*res);
		*res = temp;
	}
}

void	append_exit_code(t_data *data, t_exp_data *exp, char **res)
{
	char	*value;

	value = ft_itoa(data->exit_code);
	exp->key_len = 1;
	exp->i += exp->key_len;
	exp->start = exp->i + 1;
	append_value(data, res, value);
	free(value);
}

int	keylen(char *content, int start)
{
	int	i;

	i = start;
	while (content[i] && (ft_isalnum(content[i]) || content[i] == '_')
		&& content[i] != '\"')
		i++;
	return (i - start);
}

void	append_dollar(t_data *data, t_exp_data *exp, char *content, char **res)
{
	char	*key;
	char	*value;

	if (content[exp->i + 1] == '?')
		append_exit_code(data, exp, res);
	else if (ft_isalnum(content[exp->i + 1]) || content[exp->i + 1] == '_')
	{
		exp->key_len = keylen(content, exp->i + 1);
		key = ft_substr(content, exp->i + 1, exp->key_len);
		if (!key)
			return (free(*res), clean_exit(data, "Malloc failed", 0));
		value = data->table->get(data->table->table, key);
		value = ft_strdup(value);
		if (!value)
			free(key);
		if (!value)
			return (free(*res), clean_exit(data, "Malloc failed", 0));
		append_value(data, res, value);
		exp->i += exp->key_len;
		exp->start = exp->i + 1;
		free (key);
		free (value);
	}
}

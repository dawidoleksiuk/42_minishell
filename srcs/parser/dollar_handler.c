/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:22:06 by doleksiu          #+#    #+#             */
/*   Updated: 2026/04/16 20:09:53 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_after_dollar(t_data *data, char **content, int post_len)
{
	char	*after_dollar;
	int		content_len;

	after_dollar = NULL;
	content_len = ft_strlen(*content);
	if (content_len > post_len)
	{
		after_dollar = ft_substr(*content, post_len, content_len - post_len);
		if (!after_dollar)
			clean_exit(data, "Malloc failed", 0);
	}
	return (after_dollar);
}

void	insert_val(t_data *data, t_exp_data *exp, char **content, char *val)
{
	char	*before_dollar;
	char	*after_dollar;
	char	*res;
	char	*temp;

	res = NULL;
	before_dollar = ft_substr(*content, 0, exp->i);
	if (!before_dollar)
		clean_exit(data, "Malloc failed", 0);
	after_dollar = get_after_dollar(data, content, exp->i + exp->key_len + 1);
	res = ft_strjoin(before_dollar, val);
	free(before_dollar);
	if (!res)
		clean_exit(data, "Malloc failed", 0);
	if (after_dollar)
	{
		temp = ft_strjoin(res, after_dollar);
		free (res);
		free (after_dollar);
		if (!temp)
			clean_exit(data, "Malloc failed", 0);
		res = temp;
	}
	free(*content);
	*content = res;
}

void	handle_exit_code(t_data *data, t_exp_data *exp, char **content)
{
	char	*value;

	value = ft_itoa(data->exit_code);
	exp->key_len = 1;
	insert_val(data, exp, content, value);
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

void	insert_dollar_val(t_data *data, t_exp_data *exp, char **content)
{
	char	*key;
	char	*value;

	if ((*content)[exp->i + 1] == '?')
		handle_exit_code(data, exp, content);
	if (ft_isalnum((*content)[exp->i + 1]) || (*content)[exp->i + 1] == '_')
	{
		exp->key_len = keylen(*content, exp->i + 1);
		key = ft_substr(*content, exp->i + 1, exp->key_len);
		if (!key)
			clean_exit(data, "Malloc failed", 0);
		value = data->exec_info->envars->table->get
			(data->exec_info->envars->table->table, key);
		if (value)
			value = ft_strdup(value);
		else
			value = ft_strdup("");
		if (!value)
			clean_exit(data, "Malloc failed", 0);
		insert_val(data, exp, content, value);
		exp->i += ft_strlen(value) - 1;
		free (key);
		free (value);
	}
}

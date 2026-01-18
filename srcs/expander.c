/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:25 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/18 14:14:17 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	env_handler(char *arg)
// {

// }

char	*remove_quote(t_data *data, char *temp, char *arg, int len)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(arg, 0, len);
	temp2 = ft_strjoin(temp, temp1);
	free(temp);
	free(temp1);
	return (temp2);

}

char	*expand_text(char *arg, t_data *data)
{
	int		i;
	int		start;
	int		status;
	char	*temp;

	i = 0;
	start = 0;
	status = DEFAULT;
	temp = NULL;
	while (arg[i])
	{
		if (status == DEFAULT && arg[i] == '\'')
		{
			if (i > start)
				temp = remove_quote(data, temp, arg + start, i - start);
			status = IN_SINGLE;
		}
		else if (status == DEFAULT && arg[i] == '\"')
		{
			if (i > start)
				temp = remove_quote(data, temp, arg + start, i - start);
			status = IN_DOUBLE;
		}
		else if (status == IN_SINGLE && arg[i] == '\'')
		{
			temp = remove_quote(data, temp, arg + start, i - start);
			status = DEFAULT;
		}
		else if (status == IN_DOUBLE && arg[i] == '\"')
		{
			temp = remove_quote(data, temp, arg + start, i - start);
			status = DEFAULT;
		}
		if (((status == IN_DOUBLE || status == DEFAULT) && arg[i] == '\"') || 
			((status == IN_SINGLE || status == DEFAULT) && arg[i] == '\''))
			start = i + 1;
		i++;
	}
	temp = remove_quote(data, temp, arg + start, i - start);
	if (temp)
	{
		free(arg);
		arg = temp;
	}
	return (arg);
}

void	expander(t_data *data)
{
	char	**args;
	int		i;

	args = data->cmd_head->args;
	i = 0;
	while (args[i])
	{
		args[i] = expand_text(args[i], data);
		i++;
	}
}

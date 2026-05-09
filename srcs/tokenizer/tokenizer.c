/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:21:15 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/09 22:20:46 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token_node(t_data *data, t_token **token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		clean_exit(data, "Malloc failed", 0);
	node->content = NULL;
	node->next = NULL;
	if (*token != NULL)
		(*token)->next = node;
	else
	{
		data->token_head = node;
		*token = node;
	}
	return (node);
}

static int	get_next_word(char *line, int *i)
{
	int	status;

	status = DEFAULT;
	while (line[*i])
	{
		if (status == DEFAULT && line[*i] == '\'')
			status = IN_SINGLE;
		else if (status == DEFAULT && line[*i] == '\"')
			status = IN_DOUBLE;
		else if (status == IN_SINGLE && line[*i] == '\'')
			status = DEFAULT;
		else if (status == IN_DOUBLE && line[*i] == '\"')
			status = DEFAULT;
		if (status == DEFAULT && check_separator(line[*i]))
			break ;
		(*i)++;
	}
	if (status == IN_SINGLE || status == IN_DOUBLE)
	{
		ft_putstr_fd("minishell: bad quotes\n", 2);
		return (1);
	}
	return (0);
}

static void	get_next_operator(char *line, int *i, int *start)
{
	if (ft_strncmp(line + (*i), ">>", 2) == 0
		|| ft_strncmp(line + (*i), "<<", 2) == 0)
	{
		*start = (*i);
		(*i)++;
	}
	else if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
		*start = (*i);
	(*i)++;
}

static int	get_next_token(char *line, int *i, int *start)
{
	if (check_separator(line[*i]) == 0)
	{
		if (get_next_word(line, i) != 0)
			return (1);
	}
	else
		get_next_operator(line, i, start);
	return (0);
}

int	tokenizer(t_data *data)
{
	int		i;
	int		start;
	t_token	*current_token;

	i = 0;
	current_token = data->token_head;
	while (data->line[i])
	{
		while (data->line[i] == ' ')
			i++;
		start = i;
		if (data->line[i])
		{
			if (get_next_token(data->line, &i, &start) != 0)
				return (1);
			current_token = create_token_node(data, &current_token);
			current_token->content = ft_substr(data->line, start, i - start);
		}
	}
	assign_token_type(data);
	if (check_syntax(data) != 0)
		return (2);
	return (0);
}

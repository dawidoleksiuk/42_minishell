/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:21:15 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:33 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*last_node(t_token *node)
// {
// 	if (!node)
// 		return (node);
// 	while (node->next != NULL)
// 		node = node->next;
// 	return (node);
// }

t_token	*create_token_node(t_data *data, t_token **token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		clean_exit(data, "Malloc failed");
	node->content = NULL;
	node->next = NULL;
	if (*token != NULL)
		(*token)->next = node;
	else
	{
		data->token_head = node;
		(*token) = node;
	}
	return (node);
}

int	check_separator(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '\t')
		return (1);
	return (0);
}

void	get_next_word(t_data *data, char *line, int *i)
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
		clean_exit(data, "bad quotes");
}

void	get_next_operator(char *line, int *start, int *i)
{
	if (line[*i] == '|')
		*start = (*i);
	else if (ft_strncmp(line + (*i), ">>", 2) == 0
		|| ft_strncmp(line + (*i), "<<", 2) == 0)
	{
		*start = (*i);
		(*i)++;
	}
	else if (line[*i] == '<' || line[*i] == '>')
		*start = (*i);
	(*i)++;
}

void	tokenizer(t_data *data)
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
			if (!check_separator(data->line[i]))
				get_next_word(data, data->line, &i);
			else
				get_next_operator(data->line, &start, &i);
			current_token = create_token_node(data, &current_token);
			current_token->content = ft_substr(data->line, start, i - start);
		}
	}
	assign_token_type(data);
	check_syntax(data);
}

// int	main(void)
// {
// 	t_data data;
// 	t_token *token;
// 	t_token *temp;

// 	data.line = get_next_line(0);
// 	tokenizer(&data);
// 	token =  data.token_head;
// 	while (token)
// 	{
// 		printf("%sX, type: %d \n", token->content, token->type);
// 		free(token->content);
// 		temp = token;
// 		token = token->next;
// 		free(temp);
// 	}
// }

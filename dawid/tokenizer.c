/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:54:58 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/08 22:17:26 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

t_token *last_node(t_token *node)
{
	if (!node)
		return (node);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_token *create_token_node(t_data *data, t_token **token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	// if (!node)
	// 	clean_exit(data);
	node->content = NULL;
	node->next = NULL;
	if (*token != NULL)
		(*token)->next = node;
	else
		data->token_head = node;
	return (node);
}

void	get_next_token(char *line, int *i)
{
	int	status;

	status = DEFAULT;
	while(line[*i])
	{
		if (status == DEFAULT && line[*i] == '\'')
			status = IN_SINGLE;
		else if (status == DEFAULT && line[*i] == '\"')
			status = IN_DOUBLE;
		else if (status == IN_SINGLE && line[*i] == '\'')
			status = DEFAULT;
		else if (status == IN_DOUBLE && line[*i] == '\"')
			status = DEFAULT;
		if (status == DEFAULT && line[*i] == ' ')
			break ;
		(*i)++;
	}
}

t_token	*tokenizer(t_data *data)
{
	int		i;
	int		start;
	t_token	*current_token;

	i = 0;
	data->token_head = NULL;
	current_token = data->token_head;
	while(data->line[i])
	{
		start = i;
		get_next_token(data->line, &i);
		current_token = create_token_node(data, &current_token);
		current_token->content = ft_substr(data->line, start, i - start);
		if (data->line[i])
			i++;
	}
}

int	main(void)
{
	t_data data;
	t_token *token;
	data.line = "a co ' zaglądasz ?' xd ";
	tokenizer(&data);
	token =  data.token_head;
	while (token)
	{
		printf("%sX\n", token->content);
		token = token->next;
	}
}

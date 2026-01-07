/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:54:58 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/07 23:11:26 by doleksiu         ###   ########.fr       */
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

char *get_next_token(char *line, int *i, int par_on)
{
	char	*content;
	int start;

	start = *i;
	if (par_on)
		(*i)++;
	while(line[*i])
	{
		if (line[*i] == ' ' && par_on == 0)
			break ;
		if (((line[*i] == '\"' || line[*i] == '\'') && par_on == 1))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	content = ft_substr(line, start, *i - start);
	return (content);
}

t_token	*tokenizer(t_data *data)
{
	int		i;
	t_token	*current_token;

	i = 0;
	data->token_head = NULL;
	current_token = data->token_head;
	while(data->line[i])
	{
		if (data->line[i] != ' ')
		{
			current_token = create_token_node(data, &current_token);
			if (data->line[i] == '"' || data->line[i] == '\'')
				current_token->content = get_next_token(data->line, &i, 1);
			else
				current_token->content = get_next_token(data->line, &i, 0);
			// assign_token_type(current_token);
		}
		else
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

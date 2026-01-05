/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:54:58 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/05 18:34:36 by doleksiu         ###   ########.fr       */
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

t_token	*create_token_node(t_data *data)
{
	t_token	*node;
	t_token	*temp;

	node = malloc(sizeof(t_token));
	if (!node)
		clean_exit(data);
	node->content = NULL;
	node->next = NULL;
	temp = last_node(data->token_head);
	if (temp != NULL)
		temp->next = node;
	else
		data->token_head = node;
	return (node);
}

char *get_next_token(char *line, int *i)
{
	
}

t_token	*tokenizer(t_data *data)
{
	int		i;
	t_token	*token;

	i = 0;
	data->token_head = NULL;
	token = data->token_head;
	while(data->line[i])
	{
		if (data->line[i] != ' ')
		{
			token = create_token_node(data);
			token->content = get_next_token(data->line, &i);
			assign_token_type(token);
		}
		i++;
	}
}

int	main(void)
{
	t_data data;
	data.line = "hehe hebeh hehepbxfgb";
	tokenizer(&data);
}

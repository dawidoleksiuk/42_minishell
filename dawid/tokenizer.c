/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:54:58 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:14 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

t_token *last_node(t_token *token)
{
	if (!token)
		return (token);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	create_token_node(t_data *data)
{
	t_token	*node;
	t_token	*temp;

	node = malloc(sizeof(t_token));
	if (!node)
		clean_exit(data);
	temp = last_node(*token);
}

t_token	*tokenizer(t_data *data)
{
	t_token	*token;
	int		i;

	token = NULL;
	i = 0;
	while(data->line[i])
	{
		if (data->line[i] != ' ')
		{
			create_token_node(&token);
			token->content = get_next_token(data->line, *i);
			assign_token_type(token);
		}
		i++;
	}
}

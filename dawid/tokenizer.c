/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:54:58 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/11 13:37:15 by doleksiu         ###   ########.fr       */
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

int	check_separator(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

void	get_next_word(char *line, int *i)
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
		if (status == DEFAULT && check_separator(line[*i]))
			break ;
		(*i)++;
	}
	if (status == IN_SINGLE || status == IN_DOUBLE)
	{
		printf("bad quotes");
		exit (1);
	}
}


// void	assign_token_type(t_data *data)
// {
// 	t_token	token;

// 	token = data->token_head;

// 	while (token)
// 	{
// 		if (ft_strncmp(token->content, "|", 1))
// 			token->type = 
// 		token = token->next;
// 	}
// }

void	get_next_separator(char *line, int *start, int *i)
{

	if (line[*i] == '|')
	{
		*start = (*i) - 1;
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		*start = (*i) - 1;
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
		while (data->line[i] == ' ')
			i++;
		start = i;
		if (!check_separator(data->line[i]))
			get_next_word(data->line, &i);
		else if (check_separator(data->line[i]))
			get_next_separator(data->line, &start, &i);
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
	data.line = "2";
	tokenizer(&data);
	token =  data.token_head;
	while (token)
	{
		printf("%sX\n", token->content);
		token = token->next;
	}
}

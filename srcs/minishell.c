/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/12 17:19:53 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data	data;
	t_token	*token;

	if (isatty(STDIN_FILENO))
	{
		if (init(&data) == 1)
			clean_exit(&data, NULL);
		while (1)
		{
			prompt(&data);
			tokenizer(&data);
			if (data.line)
			{
				free(data.line);
				data.line = NULL;
			}
			token = data.token_head;
			while (token)
			{
				printf("%sX, type: %d \n", token->content, token->type);
				token = token->next;
			}
			if (data.token_head)
				free_tokens(&data);
		}
	}
	clean_exit(&data, NULL);
	return (0);
}

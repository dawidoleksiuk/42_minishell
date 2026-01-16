/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/16 21:49:21 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data	data;
	t_token	*token;
	// t_cmd *cmd;
	// int i;

	// i = 0;
	if (isatty(STDIN_FILENO))
	{
		if (init(&data) == 1)
			clean_exit(&data, NULL);
		while (1)
		{
			prompt(&data);
			tokenizer(&data);
			parser(&data);
			if (data.line)
			{
				free(data.line);
				data.line = NULL;
			}
			token = data.token_head;
			// while (token)
			// {
			// 	printf("%s, type: %d \n", token->content, token->type);
			// 	token = token->next;
			// }
			// cmd = data.cmd_head;
			// while (cmd)
			// {
			// 	i = 0;
			// 	while (cmd->args[i])
			// 	{
			// 		printf("%s \n", cmd->args[i]);
			// 		i++;
			// 	}
			// 	printf("next cmd node\n");
			// 	cmd = cmd->next;
			// }
			if (data.token_head)
				free_tokens(&data);
			if (data.cmd_head)
				free_cmd(&data);
		}
	}
	clean_exit(&data, NULL);
	return (0);
}

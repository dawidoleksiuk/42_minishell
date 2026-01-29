/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/29 19:29:42 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void print_tokens(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		printf("%s, type: %d \n", token->content, token->type);
		token = token->next;
	}
}

void print_cmds(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;

	cmd = data->cmd_head;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("args %d: %s \n", i, cmd->args[i]);
			i++;
		}
		while (cmd->redirs)
		{
			printf("file: %s, redir type: %d \n", cmd->redirs->filename, cmd->redirs->type);
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	exit_code;

	//do usuniecia
	(void) argc;
	argv[0] = NULL;
	if (isatty(STDIN_FILENO))
	{
		if (init(&data, envp) == 1)
			clean_exit(&data, NULL);
		while (1)
		{
			prompt(&data);
			tokenizer(&data);
			expander(&data);
			parser(&data);
			if (data.line)
			{
				free(data.line);
				data.line = NULL;
			}
			// print_tokens(&data);
			//print_cmds(&data);
			//make_connections(&data);
			executor(&data, data.cmd_head, &exit_code);
			free_tokens(&data);
			free_cmd(&data);
		}
	}
	clean_exit(&data, NULL);
	return (0);
}

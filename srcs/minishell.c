/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/18 17:25:38 by alusnia          ###   ########.fr       */
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

//valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	exit_code;
	size_t	i = 0;
	t_list	*node;
	t_list	**table;

	//do usuniecia
	(void) argc;
	argv[0] = NULL;
	if (isatty(STDIN_FILENO))
	{
		if (init(&data, envp) == 1)
			clean_exit(&data, NULL, 0);
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
			table = data.exec_info->envars->table;
			while (i < 63)
			{
				node = *table;
				while (node)
				{
					ft_printf("%s%s\n", node->key, node->value);
					node = node->next;
				}
				table++;
				i++;
			}
			executor(&data, data.cmd_head, &exit_code);
			free_tokens(&data);
			free_cmd(&data);
		}
	}
	clean_exit(&data, NULL, 0);
	return (0);
}

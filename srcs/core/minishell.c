/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/12 16:53:44 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_data *data)
{
	t_token	*token;

	token = data->token_head;
	while (token)
	{
		printf("%s, type: %d \n", token->content, token->type);
		token = token->next;
	}
}

void	print_cmds(t_data *data)
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
			printf("file: %s, redir type: %d \n",
				cmd->redirs->filename, cmd->redirs->type);
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
	}
}

int	minishell(t_data *data)
{
	prompt(data);
	if (g_signum != 0)
	{
		data->exit_code = 128 + g_signum;
		g_signum = 0;
	}
	if (tokenizer(data) != 0)
	{
		data->exit_code = 2;
		free_tokens(data);
		return (1);
	}
	expander(data);
	parser(data);
	// print_tokens(data);
	// print_cmds(data);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	executor(data, data->cmd_head);
	free_tokens(data);
	free_cmd(data);
	return (0);
}

//valgrind --leak-check=full --show-leak-kinds=all
// --suppressions=readline.supp ./minishell
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	if (init(&data, envp) != 0)
	{
		data.exit_code = 0;
		clean_exit(&data, NULL, data.exit_code);
	}
	while (1)
		minishell(&data);
	clean_exit(&data, NULL, data.exit_code);
	return (0);
}

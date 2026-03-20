/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/03/20 17:05:30 by doleksiu         ###   ########.fr       */
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
			printf("file: %s, redir type: %d \n", cmd->redirs->filename, cmd->redirs->type);
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
	if (tokenizer(data) == 1)
	{
		free_tokens(data);
		return (1);
	}
	expander(data);
	parser(data);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	// print_tokens(data);
	// print_cmds(data);
	//make_connections(&data);
	executor(data, data->cmd_head, &data->exit_code);
	free_tokens(data);
	free_cmd(data);
	return (0);
}

//valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	//do usuniecia
	(void) argc;
	argv[0] = NULL;
	if (init(&data, envp) == 1)
		clean_exit(&data, NULL, 0);
	while (1)
		minishell(&data);
	clean_exit(&data, NULL, 0);
	return (0);
}

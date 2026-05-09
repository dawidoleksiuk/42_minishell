/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/09 18:22:30 by doleksiu         ###   ########.fr       */
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
	argv[0] = NULL;
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

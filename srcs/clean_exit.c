/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/27 18:39:23 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char	**args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (data->cmd_head)
	{
		cmd = data->cmd_head;
		while (cmd)
		{
			if (cmd->args)
				free_args(cmd->args);
			temp = cmd;
			cmd = cmd->next;
			free(temp);
		}
		data->cmd_head = NULL;
	}
}

void	free_tokens(t_data *data)
{
	t_token	*token;
	t_token	*temp;

	if (data->token_head)
	{
		token = data->token_head;
		while (token)
		{
			if (token->content)
			{
				free(token->content);
				token->content = NULL;
			}
			temp = token;
			token = token->next;
			free(temp);
		}
		data->token_head = NULL;
	}
}

void	clean_exit(t_data *data, char *msg)
{	
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (data->error_msg)
		free(data->error_msg);
	rl_clear_history();
	if (data->line)
		free (data->line);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p_save))
		perror("error in tcsetattr");
	free_tokens(data);
	free_cmd(data);
	exit (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/12 14:20:35 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_data *data)
{
	t_token *token;
	t_token	*temp;
	
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

void	clean_exit(t_data *data, char *msg)
{
	if (data->line)
		free (data->line);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p_save))
		perror("error in tcsetattr");
	if(data->token_head)
		free_tokens(data);

	//free cmds
	if (msg)
		ft_putstr_fd(msg, 2);
	exit (0);
}

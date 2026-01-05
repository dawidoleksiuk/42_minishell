/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:46:43 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/05 20:23:58 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
Funtion takes type of redirection and returns 0 if executed correctly.
with file descriptor assigned for correct value.
If error ocurred function returns -1.
*/
static void read_input(int out, char *delimiter)
{
	char 	*str;
	size_t	len;

	len = ft_strlen(delimiter);
	str = get_next_line(0);
	while (str || (len == ft_strlen(str) && !ft_strncmp(delimiter, str, len)))
	{
		ft_putstr_fd(str, out);
		free(str);
		str = get_next_line(0);
	}
}

char	redirection(t_fd **fd, t_type *type, char *path)
{
	if (type == HEREDOC)
	{
		if (!pipe((*fd)->pipe_fd))
		{
			read_input((*fd)->pipe_fd[1], path);
			(*fd)->in = (*fd)->pipe_fd[0];
		}
	}
	else if (type == REDIR_IN)
		(*fd)->in = open(path, O_RDONLY);
	else if (type == APPEND)
		(*fd)->out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		(*fd)->out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*fd)->in < 0 || (*fd)->out < 0)
		return (-1);
	return (0);
}
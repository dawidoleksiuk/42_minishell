/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:46:43 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/05 21:33:54 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Function is printing input from the user directly into the pipe, it will
continue till user enters exactly the same input as delimiter
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

/*
Funtion takes type of redirection and returns 1 if executed correctly and
assign file descriptor to correct value. If file was impossible to open function 
will return 0, and if error ocurred function returns -1.
*/
char	redirection(t_fd **fd, t_type *type, char *path)
{
	if (type == HEREDOC)
	{
		if (!pipe((*fd)->pipe_fd))
		{
			read_input((*fd)->pipe_fd[1], path);
			(*fd)->in = (*fd)->pipe_fd[0];
		}
		else
			return (-1);
	}
	else if (type == REDIR_IN)
		(*fd)->in = open(path, O_RDONLY);
	else if (type == APPEND)
		(*fd)->out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		(*fd)->out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*fd)->in < 0 || (*fd)->out < 0)
		return (0);
	return (1);
}
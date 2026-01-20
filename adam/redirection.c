/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:46:43 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/19 08:48:14 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static void	handle_redir_error(t_type type, t_redir path)
{

	if (t
}
*/
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
Funtion takes type of redirection and returns 0 if executed correctly and
assign file descriptor to correct value. If file was impossible to open function
will assign 1 to error code, or if error ocurred function assigns 2.
*/
static t_fd	*redirection(t_fd *f_info, t_type *type, char *path)
{
	if (type == HEREDOC)
	{
		if (!pipe(f_info->pipe_fd))
		{
			read_input(f_info->pipe_fd[1], path);
			f_info->in = f_info->pipe_fd[0];
		}
		else
			return (f_info->error = 2, f_info);
	}
	else if (type == REDIR_IN)
		f_info->in = open(path, O_RDONLY);
	else if (type == APPEND)
		f_info->out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		f_info->out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (f_info->in < 0 || f_info->out < 0)
		return (f_info->error = 1, f_info);
	return (f_info);
}

/*
Function loops thru redir list and executes redir for each node.
*/
t_fd *redir(t_fd *f_info, t_redir *redir)
{
	while (redir)
	{
		f_info = redirection(f_info, redir->type, redir->filename);
		if (f_info->error)
			return (perror("minishell"), f_info);
		redir = redir->next;
	}
	return (f_info);
}
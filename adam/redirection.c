/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:46:43 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/22 08:04:32 by alusnia          ###   ########.fr       */
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
static t_exec_info	*redirection(t_exec_info *ex_info, t_type *type, char *path)
{
	if (type == HEREDOC)
	{
		if (!pipe(ex_info->pipe_fd))
		{
			read_input(ex_info->pipe_fd[1], path);
			ex_info->in = ex_info->pipe_fd[0];
		}
		else
			return (ex_info->error = 2, ex_info);
	}
	else if (type == REDIR_IN)
		ex_info->in = open(path, O_RDONLY);
	else if (type == APPEND)
		ex_info->out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		ex_info->out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ex_info->in < 0 || ex_info->out < 0)
		return (ex_info->error = 1, ex_info);
	return (ex_info);
}

/*
Function loops thru redir list and executes redir for each node.
*/
t_exec_info *redir(t_exec_info *ex_info, t_redir *redir)
{
	while (redir)
	{
		ex_info = redirection(ex_info, redir->type, redir->filename);
		if (ex_info->error)
			return (perror("minishell"), ex_info);
		redir = redir->next;
	}
	return (ex_info);
}
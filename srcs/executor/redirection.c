/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:46:43 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/07 11:38:51 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Function is printing input from the user directly into the pipe, it will
continue till user enters exactly the same input as delimiter
*/
static void read_input(t_exec_info *ex_info, int out, char *delimiter)
{
	char    *str;
	size_t  len;
	
	len = ft_strlen(delimiter) - 1;
	if (signal_action(SIGINT, &sig_handler_child) == 1 || signal_action(SIGQUIT, SIG_IGN) == 1)
		return (clean_exec(ex_info, NULL, 1, NULL));
	str = readline("> ");
	while (str && (len != ft_strlen(str) || !ft_strisequal(delimiter, str, len)))
	{
		ft_putstr_fd(str, out);
		ft_putchar_fd('\n', out);
		free(str);
		str = readline("> ");
		if (g_signum != 0)
		{
			clean_exec(ex_info, "", 128 + g_signum, NULL);
			if (str)
				free(str);
		}
	}
	if (str)
		free(str);
	close(out);
	clean_exec(ex_info, "", 0, NULL);
}

static t_exec_info	*handle_heredoc(t_exec_info *ex_info, char *delimiter)
{
	int		status;
	int		sig;

	status = 0;
	errno = 0;
	if (!pipe(ex_info->pipe_fd))
	{
		ex_info->pid = fork();
		if (ex_info->pid == -1)
			return (ex_info->error = 1, ex_info);
		else if (ex_info->pid == 0)
			read_input(ex_info, ex_info->pipe_fd[1], delimiter);
	}
	else
		return (ex_info->error = 2, ex_info);
	close(ex_info->pipe_fd[1]);
	if (signal_action(SIGINT, SIG_IGN) == 1 || signal_action(SIGQUIT, SIG_IGN) == 1)
		return (ex_info->error = 1, ex_info);
	waitpid(ex_info->pid, &status, 0);
	ex_info->in = ex_info->pipe_fd[0];
	if (WIFEXITED(status))
		errno = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			g_signum = sig;
		}
		if (sig == SIGQUIT)
		{
			g_signum = sig;
			write(1, "Quit (core dumped)\n", 20);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &ex_info->data->termios_p_save);
	if (signal_action(SIGINT, &sig_handler) == 1 || signal_action(SIGQUIT, SIG_IGN) == 1)
		return (ex_info->error = 1, ex_info);
	return (ex_info->error = errno, ex_info);
}


/*
Funtion takes type of redirection and returns 0 if executed correctly and
assign file descriptor to correct value. If file was impossible to open function
will assign 1 to error code, or if error ocurred function assigns 2.
*/
static t_exec_info	*redirection(t_exec_info *ex_info, t_type type, char *path)
{
	if (type == HEREDOC)
		ex_info = handle_heredoc(ex_info, path);
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
	ex_info->redir_in = 0;
	ex_info->redir_out = 0;
	ex_info->error = 0;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (ex_info->in && ex_info->redir_in)
				close(ex_info->in);
			ex_info->redir_in = 1;
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
		{
			if (ex_info->out && ex_info->redir_out)
				close(ex_info->out);
			ex_info->redir_out = 1;
		}
		ex_info = redirection(ex_info, redir->type, redir->filename);
		if (ex_info->error && ex_info->error != errno)
			return (ex_info->error = errno, perror("minishell"), ex_info);
		redir = redir->next;
	}
	return (ex_info);
}
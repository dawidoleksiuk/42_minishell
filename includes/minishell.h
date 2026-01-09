/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/09 15:51:53 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../dawid/tokenizer.h"
# include "../dawid/parser.h"
# include "../adam/redirections.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line.h"
# include "errno.h"
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
// # include <sys/types.h>
# include <unistd.h>
# include <termios.h>

typedef struct s_fd
{
	int		in;
	int		pipe_fd[2];
	int		out;
	pid_t	pid;
} t_fd;

typedef struct s_data
{
	char			**envp;
	struct termios	termios_p_save;

	char			*line;
	t_token			*token_head;
	t_cmd			*cmd_head;
	t_fd			*f_info;
} t_data;

// clean_exit.c
void	clean_exit(t_data *data);

// init.c
void	prompt(t_data *data);
int	init(t_data *data);

// signals.c 
void	sig_handler(int sig);
int	config_sigaction(struct sigaction *sa);
int	signals(void);

// redirections.c
char	redirection(t_fd **fd, t_redir_type *type, char *path);

#endif
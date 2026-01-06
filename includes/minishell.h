/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/06 16:09:02 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../dawid/tokenizer.h"
# include "../dawid/parser.h"
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
	int	in;
	int	pipe_fd[2];
	int	out;
} t_fd;

typedef struct s_data
{
	char			**envp;
	struct termios	termios_p_save;

	int				fd_in;
	int				fd_out;
	char			*line;
	t_token			*token_head;
	t_cmd			*cmd_head;
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

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/05 21:37:13 by alusnia          ###   ########.fr       */
=======
/*   Updated: 2026/01/06 15:01:29 by doleksiu         ###   ########.fr       */
>>>>>>> 64f257e (creating first minishell files in srcs, moving gnl to libft, updading Makefile)
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../dawid/tokenizer.h"
<<<<<<< HEAD
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
=======
# include "../dawid/parser.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line.h"
>>>>>>> 64f257e (creating first minishell files in srcs, moving gnl to libft, updading Makefile)
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
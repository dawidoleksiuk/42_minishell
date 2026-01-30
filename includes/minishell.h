/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/30 20:35:15 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./parser.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line.h"
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
// # include <sys/types.h>
# include <unistd.h>
# include <termios.h>

typedef	struct s_exp_data
{
	int	i;
	int	start;
	int	status;
} t_exp_data;

typedef struct s_envp
{
	char			*name;
	char			*content;
	struct s_envp	*next;
} t_envp;

typedef struct s_exec_info
{
	int				in;
	int				*pipe_fd;
	int				out;
	unsigned char	error;
	char			is_start;
	char			redir_in;
	char			redir_out;
	char			*path;
	char			*temp;
	char			*home_dir;
	char			**catalogs;
	char			**envp;
	t_cmd			*cmd;
	pid_t			pid;
	struct s_data	*data;
} t_exec_info;

typedef struct s_data
{
	struct termios	termios_p_save;
	char			*line;
	char			*error_msg;
	t_exec_info		*exec_info;
	t_token			*token_head;
	t_cmd			*cmd_head;
	t_exp_data		exp_data;
} t_data;



// clean_exit.c
void	free_cmd(t_data *data);
void	free_tokens(t_data *data);
void	clean_exit(t_data *data, char *msg);

// init.c
void	prompt(t_data *data);
int	init(t_data *data, char **envp);

// signals.c 
void	sig_handler(int sig);
int	config_sigaction(struct sigaction *sa);
int	signals(void);

// redirections.c
// unsigned char	redirection(t_fd **fd, t_redir_type *type, char *path);

// tokenizer.c
void	tokenizer(t_data *data);

//tokenizer_2.c
void	assign_token_type(t_data *data);
void	check_syntax(t_data *data);

// parser.c
void	parser(t_data *data);

// expander.c
void	expander(t_data *data);

// redirection.c
t_exec_info *redir(t_exec_info *ex_info, t_redir *redir);

// executor.c
void	executor(t_data *data, t_cmd *cmd_head, char *exit_code);

#endif
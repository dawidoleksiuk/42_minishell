/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
/*   Updated: 2026/04/16 20:39:55 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./parser.h"
# include "libftplus.h"
# include "../srcs/hash_table/hash_table.h"
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

typedef struct s_envar
{
	char			*curr_dir;
	char			*home_dir;
	char			**catalogs;
	char			**envp;
	t_env_table		*table;
}	t_envar;

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
	t_envar			*envars;
	t_cmd			*cmd;
	pid_t			pid;
	struct s_data	*data;
}	t_exec_info;

typedef struct s_data
{
	struct termios	termios_p_save;
	char			*line;
	char			*error_msg;
	char			*prev_exit;
	unsigned char	exit_code;
	t_exec_info		*exec_info;
	t_token			*token_head;
	t_cmd			*cmd_head;
	t_exp_data		exp_data;
}	t_data;

extern volatile sig_atomic_t	g_signum;

// clean_exit.c
void			free_cmd(t_data *data);
void			free_tokens(t_data *data);
void			clean_exec(t_exec_info *exec_info, char *msg, int exit_code, void *bonus);
void			clean_exit(t_data *data, char *msg, int exit_code);
void			put_msg(char *msg);

// init.c
void			prompt(t_data *data);
int				init(t_data *data, char **envp);
struct termios	set_terminal_settings(t_data *data, int c_on);

// signals.c 
void			sig_handler(int sig);
void			sig_handler_child(int sig);
int				config_sigaction(struct sigaction *sa);
int				signals(void);
int				signal_action(int sig, void *handler);

// redirection.c
t_exec_info		*redir(t_exec_info *ex_info, t_redir *redir);

// executor.c
void			executor(t_data *data, t_cmd *cmd_head, unsigned char *exit_code);

//built-ins
int				ft_pwd(t_envar **envar);
int				ft_cd(t_envar **envar, char *path);
void			ft_echo(int	fd, char **args);
void			ft_env(t_env_table *table, int fd);
void			ft_unset(t_env_table **table, char **args);
void			ft_exit(t_data *data, char **args);
void			ft_export(t_exec_info *exec, t_env_table **table, char **args, int fd);

#endif
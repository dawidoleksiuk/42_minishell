/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
/*   Updated: 2026/02/23 17:54:46 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./parser.h"
# include "libftplus.h"
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

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
} t_list;

typedef	struct s_exp_data
{
	int	i;
	int	start;
	int	status;
} t_exp_data;

typedef struct s_envar
{
	char			*curr_dir;
	char			*home_dir;
	char			**catalogs;
	char			**envp;
	t_list			**table;
} t_envar;

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
} t_exec_info;

typedef struct s_data
{
	struct termios	termios_p_save;
	char			*line;
	char			*error_msg;
	unsigned char	exit_code;
	t_exec_info		*exec_info;
	t_token			*token_head;
	t_cmd			*cmd_head;
	t_exp_data		exp_data;
} t_data;

extern volatile sig_atomic_t	g_signum;

// clean_exit.c
void	free_cmd(t_data *data);
void	free_tokens(t_data *data);
void	clean_exec(t_exec_info *exec_info, char *msg, int exit_code, void *bonus);
void	clean_exit(t_data *data, char *msg, int exit_code);

// init.c
void	prompt(t_data *data);
int	init(t_data *data, char **envp);
void	init_termios (t_data *data, int c_on);

// signals.c 
void	sig_handler(int sig);
int	config_sigaction(struct sigaction *sa);
int	signals(void);
int	signal_action(int sig, void *handler);

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
void	executor(t_data *data, t_cmd *cmd_head, unsigned char *exit_code);

//table.c
t_list	**init_table(char **envp);
int		table_mod(t_list **ptr, char *key, char *value);
int		table_add(t_list **node, char *key, char *value);
t_list	*table_del(t_list *ptr, char *key);
void	table_clear(t_list **table);

//table_utils.c
ssize_t	table_get_i(char c);
void	clear_node(t_list *node);
t_list	*table_new_node(t_list *node);
int		table_sep_string(char *str, char **key, char **value);
char	*table_find_value(t_list **table, char *key);

//built-ins
int		ft_pwd(t_envar **envar);
int		ft_cd(t_envar **envar, char *path);
void	ft_echo(int	fd, char **args);
#endif
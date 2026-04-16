/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:39:33 by doleksiu          #+#    #+#             */
/*   Updated: 2026/04/16 20:41:59 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H	
# define PARSER_H

//COMMANDS
/* ls -l > plik1.txt < input.dat - example of a
 more complex case with two files we need to take into account */

// typedef enum	e_redir_type
// {
// 	P_REDIR_IN, // <
// 	P_REDIR_OUT, // >
// 	P_HEREDOC, // <<
// 	P_APPEND // >>
// }	t_redir_type;

# include "./tokenizer.h"

typedef struct s_data	t_data;

typedef struct s_redir
{
	t_type			type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exp_data
{
	int		i;
	char	c;
	int		start;
	int		status;
	int		key_len;
}	t_exp_data;

// parser.c
void	parser(t_data *data);

//parser_utils.c
t_cmd	*new_cmd_node(t_data *data, t_cmd *cmd);
int		copy_args(t_data *data, t_token *token, t_cmd *cmd);
t_token	*add_cmd(t_data *data, t_token *token, t_cmd *cmd);
t_redir	*new_redir_node(t_data *data, t_cmd *cmd);
t_token	*add_redir(t_data *data, t_token *token, t_cmd *cmd);

// token_processor.c
void	expand_tokens(t_data *data);

//dollar_handler.c
void	insert_dollar_val(t_data *data, t_exp_data *exp, char **content);

#endif
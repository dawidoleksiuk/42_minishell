/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:39:33 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/31 12:16:28 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H	
# define PARSER_H

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

// parser.c
void	parser(t_data *data);

//parser_utils.c
t_cmd	*new_cmd_node(t_data *data, t_cmd *cmd);
int		realloc_args(t_data *data, t_token *token, t_cmd *cmd);
t_token	*add_args(t_data *data, t_token *token, t_cmd *cmd);
t_redir	*new_redir_node(t_data *data, t_cmd *cmd);
t_token	*add_redir(t_data *data, t_token *token, t_cmd *cmd);

#endif
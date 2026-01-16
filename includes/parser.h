/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:39:33 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/15 17:43:20 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H	
# define PARSER_H

//COMMANDS
// ls -l > plik1.txt < input.dat - example of a more complex case with two files we need to take into account

// typedef enum	e_redir_type
// {
// 	P_REDIR_IN, // <
// 	P_REDIR_OUT, // >
// 	P_HEREDOC, // <<
// 	P_APPEND // >>
// }	t_redir_type;

# include "./tokenizer.h"

typedef struct s_redir
{
	t_type			type;
	char			*filename;
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
} t_cmd;

#endif
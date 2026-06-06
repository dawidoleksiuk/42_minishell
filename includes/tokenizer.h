/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:22:09 by doleksiu          #+#    #+#             */
/*   Updated: 2026/06/06 11:39:59 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define DEFAULT 0
# define IN_SINGLE 1
# define IN_DOUBLE 2

typedef struct s_data	t_data;

typedef enum e_type
{
	WORD, //0
	PIPE, //1
	REDIR_IN, // < 2
	REDIR_OUT, // > 3
	HEREDOC, // << 4
	APPEND, // >> 5
}	t_type;

typedef struct s_token
{
	char			*content;
	int				was_quoted;
	t_type			type;
	struct s_token	*next;
}	t_token;

//tokenizer.c
int		tokenizer(t_data *data);

//tokenizer_utils.c
void	assign_token_type(t_data *data);
int		check_separator(char c);
int		check_syntax(t_data *data);

#endif
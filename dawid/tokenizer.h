/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:55:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/08 22:12:08 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// https://mvsrgc.xyz/posts/Write-a-Shell-Tokenizer-in-C/
// TOKENS
# define DEFAULT 0
# define IN_SINGLE 1
# define IN_DOUBLE 2

typedef enum	e_type
{
	WORD,
	PIPE,
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND // >>
} t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
} t_token;

#endif
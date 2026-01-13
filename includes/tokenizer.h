/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:22:09 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/13 18:25:28 by doleksiu         ###   ########.fr       */
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
	WORD, //0
	PIPE, //1
	REDIR_IN, // < 2
	REDIR_OUT, // > 3
	HEREDOC, // << 4
	APPEND, // >> 5
} t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
} t_token;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:55:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/04 15:26:28 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// https://mvsrgc.xyz/posts/Write-a-Shell-Tokenizer-in-C/
// TOKENS

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
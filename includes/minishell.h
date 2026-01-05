/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:40:44 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/05 20:10:58 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "dawid/tokenizer.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "errno.h"

typedef struct s_fd
{
	int	in;
	int	pipe_fd[2];
	int	out;
} t_fd;


typedef struct s_data
{
	int	fd_in;
	int	fd_out;
} t_data;

#endif
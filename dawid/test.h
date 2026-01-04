/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:46:18 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/04 16:02:29 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "./tokenizer.h"
# include "./parser.h"
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
// # include <sys/types.h>
# include <unistd.h>
# include <termios.h>

volatile sig_atomic_t	g_signum;

typedef struct s_data
{
	char			**envp;
	struct termios	termios_p_save;

	char			*line;
	t_token			*token_head;
	t_cmd			*cmd_head;

} t_data;

void	clean_exit(t_data *data);

#endif

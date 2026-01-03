/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:43:38 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/03 10:57:11 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

void	sig_handler(int sig)
{
	struct termios_p tp;

	g_signum = sig;
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}


int	config_sigaction(struct sigaction *sa)
{
	bzero(sa, sizeof(sa));
	if ((sigaddset(&sa->sa_mask, SIGINT) == -1) 
		|| (sigaddset(&sa->sa_mask, SIGQUIT) == -1))
		return (1);
	sa->sa_handler = &sig_handler;
	return (0);
}

int	signals(void)
{
	struct sigaction	sa;
	if (config_sigaction(&sa) == 1)
		return (1);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (1);
	return (0);
}

//prompting for an input, 
//when CTRL+D clreas rl history and closes program
//if we get input, it adds it to history

void	prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		rl_clear_history();
		write (1, "exit", 4);
		exit (0);
	}
	if (line[0] != '\0')
		add_history(line);
	free (line);
}

int	main(void)
{
	if (signals() == 1)
		return (1);
	while (1)
	{
		prompt();
	}
}

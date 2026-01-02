/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:43:38 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/02 22:45:20 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

void	sig_handler(int sig)
{
	g_signum = sig;
	if (sig == SIGINT)
	{
		printf("lala");
		// rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		printf("papa");
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

void	prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
	add_history(line);
	printf("%s \n", line);
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

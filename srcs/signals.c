/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:52 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/24 18:21:45 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signum;

void	sig_handler(int sig)
{
	g_signum = sig;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	config_sigaction(struct sigaction *sa)
{
	ft_bzero(sa, sizeof(*sa));
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
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (1);
	return (0);
}

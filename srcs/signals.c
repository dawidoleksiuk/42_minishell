/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:52 by doleksiu          #+#    #+#             */
/*   Updated: 2026/03/13 09:05:21 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sig_handler_child(int sig)
{
	g_signum = sig;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "^C", 2);
		close(0);
	}
}

int	signal_action(int sig, void *handler)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if ((sigaddset(&sa.sa_mask, SIGINT) == -1)
		|| (sigaddset(&sa.sa_mask, SIGQUIT) == -1))
		return (1);
	//sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	if (sigaction(sig, &sa, NULL) == -1)
		return (1);
	return (0);
}

// int	config_sigaction(struct sigaction *sa)
// {
// 	ft_bzero(sa, sizeof(*sa));
// 	if ((sigaddset(&sa->sa_mask, SIGINT) == -1)
// 		|| (sigaddset(&sa->sa_mask, SIGQUIT) == -1))
// 		return (1);
// 	sa->sa_handler = &sig_handler;
// 	return (0);
// }

// int	signals(void)
// {
// 	struct sigaction	sa;

// 	if (config_sigaction(&sa) == 1)
// 		return (1);
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		return (1);
// 	sa.sa_handler = SIG_IGN;
// 	if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 		return (1);
// 	return (0);
// }



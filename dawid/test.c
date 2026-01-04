/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:43:38 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/04 16:27:14 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

// syntax of the CL https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html

void	clean_exit(t_data *data)
{
	if (data->line)
		free (data->line);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->termios_p_save))
		perror("error in tcsetattr");
	//free tokens
	//free cmds
	exit (0);
}

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
	bzero(sa, sizeof(*sa));
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

//prompting for an input, 
//when CTRL+D clreas rl history and closes program
//if we get input, it adds it to history
void	prompt(t_data *data)
{
	data->line = readline("minishell$ ");
	if (!data->line)
	{
		rl_clear_history();
		write (1, "exit\n", 5);
		clean_exit(data);
	}
	if (data->line[0] != '\0')
		add_history(data->line);
	free (data->line);
}

// termios https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
// https://www.gnu.org/software/libc/manual/html_node/Setting-Modes.html
// rl_catch_signals https://www.manpagez.com/info/rlman/rlman-5.2/rlman_43.php

int	init(t_data *data)
{
	struct termios termios_p;

	rl_catch_signals = 0;
	bzero(data, sizeof(t_data));
	if (tcgetattr(STDIN_FILENO, &termios_p) < 0)
	{
		perror("error in tcgetattr");
		clean_exit(data);
	}
	data->termios_p_save = termios_p;
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) < 0)
	{
		perror("error in tcsetattr");
		clean_exit(data);
	}
	if (signals() == 1)
		return (1);
	return (0);
}

int	main(void)
{
	t_data	data;

	if (isatty(STDIN_FILENO))
	{
		if (init(&data) == 1)
			clean_exit(&data);
		while (1)
			prompt(&data);
		// tokenizer(data);
	}
	return (0);
}

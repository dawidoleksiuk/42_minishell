/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:01:32 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 15:03:04 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
in interactive mode:
prompting for an input, 
if we get input, it adds it to history
when CTRL+D, clears rl history and closes program
in non-interactive mode:
reads from the file descriptor 0
*/

void	prompt(t_data *data)
{
	int	line_len;

	if (isatty(STDIN_FILENO))
	{
		data->line = readline("minishell$ ");
		if (!data->line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			clean_exit(data, NULL, data->exit_code);
		}
		if (data->line[0] != '\0')
			add_history(data->line);
	}
	else
	{
		data->line = get_next_line(STDIN_FILENO);
		if (!data->line)
			clean_exit(data, NULL, data->exit_code);
		line_len = ft_strlen(data->line);
		if (line_len > 0 && data->line[line_len - 1] == '\n')
			data->line[line_len - 1] = '\0';
	}
}

int	get_terminal_settings(struct termios *termios_p)
{
	if (tcgetattr(STDIN_FILENO, termios_p) == 0)
		return (0);
	return (1);
}
/*
turns off termios flag for signal output (^C, ^\ etc.) in terminal
*/

int	disable_echoctl(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == 0)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) != 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	init_signals(t_data *data)
{
	rl_catch_signals = 0;
	if (get_terminal_settings(&data->termios_p_save) != 0)
		return (1);
	if (disable_echoctl() != 0)
		return (1);
	if (setup_signal(SIGINT, &sig_handler) || setup_signal(SIGQUIT, SIG_IGN))
		return (1);
	return (0);
}

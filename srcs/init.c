/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:35:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/06 14:49:03 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//prompting for an input, 
//when CTRL+D clears rl history and closes program
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
// sets variables to zero
// turns off termios flag for signal output (^C, ^\ etc.) in terminal
// sets signal handling

int	init(t_data *data)
{
	struct termios termios_p;

	rl_catch_signals = 0;
	ft_bzero(data, sizeof(t_data));
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

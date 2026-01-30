/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:35:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/30 20:47:48 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//prompting for an input, 
//when CTRL+D clears rl history and closes program
//if we get input, it adds it to history
void	prompt(t_data *data)
{
	data->line = readline("minishell$ ");
	// data->line = get_next_line(0);
	if (!data->line)
	{
		write (1, "exit\n", 5);
		clean_exit(data, NULL);
	}
	if (data->line[0] != '\0')
		add_history(data->line);
}

// termios https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
// https://www.gnu.org/software/libc/manual/html_node/Setting-Modes.html
// rl_catch_signals https://www.manpagez.com/info/rlman/rlman-5.2/rlman_43.php
// sets variables to zero
// turns off termios flag for signal output (^C, ^\ etc.) in terminal
// sets signal handling
int	init_signals(t_data *data)
{
	struct termios	termios_p;

	rl_catch_signals = 0;
	ft_bzero(data, sizeof(t_data));
	if (tcgetattr(STDIN_FILENO, &termios_p) < 0)
	{
		perror("error in tcgetattr");
		clean_exit(data, NULL);
	}
	data->termios_p_save = termios_p;
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) < 0)
	{
		perror("error in tcsetattr");
		clean_exit(data, NULL);
	}
	if (signals() == 1)
		return (1);
	return (0);
}

static int	get_envp(t_data *data, char **envp)
{
	char	*str;

	data->exec_info->envp = envp;
	str = getenv("PATH");
	if (str)
		data->exec_info->catalogs = ft_split(str, ':');
	data->exec_info->home_dir = getenv("HOME");
	return (0);
}

int	init(t_data *data, char **envp)
{
	data->line = NULL;
	data->token_head = NULL;
	data->cmd_head = NULL;
	data->exp_data.i = 0;
	data->exp_data.start = 0;
	data->exp_data.status = DEFAULT;
	if (init_signals(data))
		return (1);
	data->exec_info = ft_calloc(1, sizeof(t_exec_info));
	if (!data->exec_info || get_envp(data, envp))
		return (1);
	data->exec_info->pipe_fd = ft_calloc(2, sizeof(int));
	if (!data->exec_info->pipe_fd)
		return (1);
	return (0);
}

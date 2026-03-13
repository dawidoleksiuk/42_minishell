/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:35:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/03/06 10:56:52 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		clean_exit(data, NULL, 0);
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

struct termios	init_termios (int symbol_on)
{
	struct termios	termios_p;
	struct termios	termios_p_copy;

	ft_bzero(&termios_p_copy, sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, &termios_p) == 0)
	{
		termios_p_copy = termios_p;
		if (!symbol_on)
			termios_p.c_lflag &= ~ECHOCTL;
		if (symbol_on)
			termios_p.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	}
	return (termios_p_copy);
}

int	init_signals(t_data *data)
{
	rl_catch_signals = 0;
	data->termios_p_save = init_termios(0);
	if (signal_action(SIGINT, &sig_handler) == 1 || signal_action(SIGQUIT, SIG_IGN) == 1)
		return (1);
	return (0);
}

static int	get_envp(t_data *data, char **envp)
{
	char	*str;

	data->exec_info->envars = ft_calloc(1, sizeof(t_envar));
	if (!data->exec_info->envars)
		return (1);
	data->exec_info->envars->envp = envp;
	data->exec_info->envars->table = init_table(envp);
	str = getenv("PATH");
	if (str)
		data->exec_info->envars->catalogs = ft_split(str, ':');
	data->exec_info->envars->home_dir = getenv("HOME");
	str = getenv("PWD");
	data->exec_info->envars->curr_dir = ft_strdup(str);
	if (!data->exec_info->envars->curr_dir || !data->exec_info->envars->envp)
		return (1);
	return (0);
}

int	init(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	if (init_signals(data))
		return (1);
	data->exec_info = ft_calloc(1, sizeof(t_exec_info));
	if (!data->exec_info || get_envp(data, envp))
		return (1);
	data->exec_info->data = data;
	return (0);
}

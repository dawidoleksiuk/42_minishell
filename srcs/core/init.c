/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:35:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/10 00:09:15 by doleksiu         ###   ########.fr       */
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

// termios https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
// https://www.gnu.org/software/libc/manual/html_node/Setting-Modes.html
// rl_catch_signals https://www.manpagez.com/info/rlman/rlman-5.2/rlman_43.php


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

static int	get_envp(t_data *data, char **envp)
{
	char	*str;

	data->exec_info->envars = ft_calloc(1, sizeof(t_envar));
	if (!data->exec_info->envars)
		return (1);
	data->exec_info->envars->envp = envp;
	data->exec_info->envars->table = table_init(envp);
	if (!data->exec_info->envars->table)
		return (1);
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
	if (isatty(STDIN_FILENO) && init_signals(data) == 1)
		return (1);
	data->exec_info = ft_calloc(1, sizeof(t_exec_info));
	data->exec_info->out = 1;
	if (!data->exec_info || get_envp(data, envp))
		return (1);
	data->exec_info->data = data;
	return (0);
}

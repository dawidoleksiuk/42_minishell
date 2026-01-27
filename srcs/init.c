/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:35:08 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/27 18:53:11 by alusnia          ###   ########.fr       */
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

static int	check_for_important(t_data *data, char *envp)
{
	if (!ft_strncmp(envp, "PATH=", 5))
	{
		data->exec_info->catalogs = ft_split(envp + 5, ':');
		return (1);
	}
	else if (!ft_strncmp(envp, "HOME=", 5))
	{
		data->exec_info->home_dir = envp + 5;
		return (1);
	}
	else
		return (0);
}

static int	get_envp(t_data *data, char **envp)
{
	size_t	i;
	t_envp	*node;

	ft_bzero(data->exec_info, sizeof(t_exec_info));
	i = 0;
	data->exec_info->envp = malloc(sizeof(t_envp));;
	node = data->exec_info->envp;
	while (envp[i])
	{
		if (!node)
			return (1);
		while (check_for_important(data, envp[i]))
			i++;
		{
			node->name = envp[i];
			node->content = ft_strchr(envp[i++], '=');
			node->content[0] = 0;
			node->content++;
		}
		if (envp[i])
		{
			node->next = malloc(sizeof(t_envp));
			node = node->next;
		}
		else
			node->next = NULL;
	}
	while (data->exec_info->envp)
	{
		ft_printf("%s\n%s\n\n", data->exec_info->envp->name, data->exec_info->envp->content);
		data->exec_info->envp = data->exec_info->envp->next;
	}
	ft_printf("%s\n", data->exec_info->home_dir);
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
	data->exec_info = malloc(sizeof(t_exec_info));
	if (!data->exec_info || get_envp(data, envp))
		return (1);
	return (0);
}

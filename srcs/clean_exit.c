/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:39:17 by doleksiu          #+#    #+#             */
/*   Updated: 2026/01/06 14:48:51 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

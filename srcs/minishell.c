/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/06 16:09:10 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

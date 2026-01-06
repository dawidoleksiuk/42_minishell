/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:39 by alusnia           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/05 21:36:36 by alusnia          ###   ########.fr       */
=======
/*   Updated: 2026/01/06 15:04:43 by doleksiu         ###   ########.fr       */
>>>>>>> 64f257e (creating first minishell files in srcs, moving gnl to libft, updading Makefile)
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
int main(void)
{
	ft_printf("test\n");
=======
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
>>>>>>> 64f257e (creating first minishell files in srcs, moving gnl to libft, updading Makefile)
	return (0);
}

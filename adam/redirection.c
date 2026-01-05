/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:46:43 by alusnia           #+#    #+#             */
/*   Updated: 2026/01/05 19:26:00 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
Funtion takes type of redirection and returns fd
for the file pointed by the path.
if type is to read from stdin, path is a delimiter and function returns 0.
If error ocurred function returns -1.
*/
int	redirection(t_type *type, char *path)
{
	if (type == HEREDOC)
			return(0);
	else if (type == REDIR_IN)
		return(open(path, O_RDONLY));
	else if (type == APPEND)
		return(open(path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (type == REDIR_OUT)
		return(open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}
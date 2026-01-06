/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:44:11 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/22 21:21:45 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_str_list	*start_lst;
	t_str_list			*lst;
	ssize_t				count;
	char				*str;

	str = NULL;
	count = 0;
	lst = look_for_lst(fd, &start_lst);
	while (count++ < (ssize_t)lst->line_len && lst)
	{
		if (lst->content[count - 1] == '\n' || lst->content[count - 1] == '\0')
			return (export_line(lst, &start_lst, 0));
	}
	while ((count >= 1) && lst)
	{
		str = malloc(BUFFER_SIZE);
		count = read_buffer(str, fd, &count, lst);
		free(str);
	}
	if (count == 0 && lst)
		return (export_line(lst, &start_lst, 0));
	else
		return (export_line(lst, &start_lst, -1));
}

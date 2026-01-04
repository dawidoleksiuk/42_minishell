/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:23:20 by alusnia           #+#    #+#             */
/*   Updated: 2025/12/01 10:52:15 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_str_list
{
	char				*content;
	int					fd;
	size_t				line_len;
	struct s_str_list	*next;
	struct s_str_list	*prev;
}	t_str_list;

char		*get_next_line(int fd);
char		*del_lst_content(t_str_list *lst, t_str_list ***start_lst,
				size_t *i, char *str);
char		*export_line(t_str_list *lst, t_str_list **start_lst,
				ssize_t count);
t_str_list	*create_node(t_str_list *lst, t_str_list *prev,
				t_str_list ***start_lst, int fd);
t_str_list	*look_for_lst(int fd, t_str_list **start_lst);
int			read_buffer(char *str, int fd, ssize_t *count, t_str_list *lst);

#endif

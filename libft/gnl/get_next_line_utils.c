/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:44:50 by alusnia           #+#    #+#             */
/*   Updated: 2025/10/22 21:21:47 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*del_lst_content(t_str_list *lst, t_str_list ***start_lst,
	size_t *i, char *str)
{
	char	*new_content;

	lst->line_len -= i[0];
	if (lst->line_len > 0)
	{
		new_content = malloc(lst->line_len);
		while (i[1]++ < lst->line_len)
			new_content[i[1] - 1] = lst->content[i[0] + i[1] - 1];
	}
	if ((i[0] || lst->line_len > 0) && lst->content)
		free(lst->content);
	if (lst->line_len == 0)
	{
		if (lst->prev)
			(lst->prev)->next = lst->next;
		else
			**start_lst = lst->next;
		if (lst->next)
			(lst->next)->prev = lst->prev;
		free(lst);
	}
	else
		lst->content = new_content;
	return (str);
}

char	*export_line(t_str_list *lst, t_str_list **start_lst, ssize_t count)
{
	char	*str;
	size_t	i[2];

	str = NULL;
	i[0] = 0;
	i[1] = 0;
	if (count == 0)
	{
		while (lst->content[count] != '\n' && lst->content[count++])
			;
		if (lst->content[count] == '\n')
			count++;
	}
	if (count == -1)
		return (del_lst_content(lst, &start_lst, i, NULL));
	str = malloc(count + 1);
	if (!str)
		return (NULL);
	while (i[0] < (size_t)count)
	{
		str[i[0]] = lst->content[i[0]];
		i[0]++;
	}
	str[i[0]] = '\0';
	return (del_lst_content(lst, &start_lst, i, str));
}

t_str_list	*create_node(t_str_list *lst, t_str_list *prev,
	t_str_list ***start_lst, int fd)
{
	t_str_list	*new;

	new = malloc(sizeof(t_str_list));
	if (!new)
		return (NULL);
	if (lst)
		lst->next = new;
	else
		**start_lst = new;
	new->fd = fd;
	new->line_len = 0;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

t_str_list	*look_for_lst(int fd, t_str_list **start_lst)
{
	t_str_list	*lst;

	if (!*start_lst)
		return (*start_lst = create_node(NULL, NULL, &start_lst, fd));
	lst = *start_lst;
	while (lst->next && fd != lst->fd)
	{
		lst = lst->next;
	}
	if (lst->fd == fd)
		return (lst);
	else
		return (create_node(lst, lst, &start_lst, fd));
}

int	read_buffer(char *str, int fd, ssize_t *count, t_str_list *lst)
{
	ssize_t		i;
	size_t		j;
	char		*content;

	content = NULL;
	j = 0;
	i = read(fd, str, BUFFER_SIZE);
	if (i <= 0)
		return (i - 1);
	content = malloc(lst->line_len + i);
	if (!content)
		return (-1);
	while (j++ < lst->line_len && lst->line_len != 0)
		content[j - 1] = lst->content[j - 1];
	while (j - lst->line_len <= (size_t)i)
	{
		content[j - 1] = str[j - lst->line_len - 1];
		if (content[j - 1] == '\0' || content[j++ - 1] == '\n')
			*count = 0;
	}
	if (i != 0 && lst->line_len != 0)
		free(lst->content);
	lst->content = content;
	lst->line_len += i;
	return (*count);
}

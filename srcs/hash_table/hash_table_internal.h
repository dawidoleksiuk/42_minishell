/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:26:58 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 14:57:02 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_INTERNAL_H
# define HASH_TABLE_INTERNAL_H
# define VARIABLES_HASH_BUCKETS 1024 //Number of buckets inside hash table
# define FNV_PRIME 16777619 //Prime numer used in orginal bash to hash a table
# define ALL 1
# define ONE 0
# include "libftplus.h"

typedef enum e_connect
{
	REGULAR,
	SORTED,
}	t_connect;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	**next;
	struct s_list	**prev;

}	t_list;

typedef struct s_table
{
	t_list	**nodes;
	t_list	*sorted_list;
	t_list	*env;
	size_t	n_of_nodes;
}	t_table;

//core.c
void	free_list(t_list *list, int flag);

//methods.c
char	*get(t_table *table, char *key);
int		set(t_table **table, char *str);
void	display(t_table *table, char sorted, int fd);
void	del(t_table **table, char *key);

//utils.c
size_t	hash_fnv1(char *key);
int		seperate_string(char *str, char **key, char **value);
int		verify_key(char *key);
t_list	*find(t_table *table, char *key);

//operations.c
int		table_add(t_table **table, char *key, char *value);
void	display_sorted(t_list *list, int fd);
void	display_regular(t_list **list, int fd);

//node_operations.c
int		add_node(t_list **node, t_list *prev, char *key, char *value);
int		node_insert(t_list **new, t_list **prev,
			t_list **next, t_connect index);
void	connect_nodes(t_list ***prev, t_list ***next, t_connect index);
void	replace_node(t_table **table, char *key);

//sort.c
void	insert_sorted_list(t_list **head, t_list *new_node);
void	sort(t_table **table);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:26:58 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 13:29:41 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_INTERNAL_H
# define HASH_TABLE_INTERNAL_H
# define VARIABLES_HASH_BUCKETS 1024 //Number of buckets inside hash table
# define FNV_PRIME 16777619 //Prime numer used in orginal bash to hash a table
# include <stdlib.h>
# include "libftplus.h"

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
	struct s_list	*next_sorted;
} t_list;

typedef struct s_table
{
	t_list	**nodes;
	t_list	*sorted_list;
	t_list	*env;
	size_t	n_of_nodes;
} t_table;


//table_utils.c
size_t	hash_fnv1(char *key);
int		seperate_string(char *str, char **key, char **value);
int		verify_key(char *key);

//table_operations.c
char	*table_get(t_table *table, char *key);
int 	table_add(t_table **table, char *key, char *value);
int		table_set(t_table **table, char *str);

//node_operations.c
int add_node(t_list **node, char *key, char *value);
int	node_insert(t_list **new, t_list **prev, t_list *next, char sorted);

//table_sort.c
void	sort(t_table **table);
#endif
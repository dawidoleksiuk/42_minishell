/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:27:01 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 13:35:30 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct s_table t_table;

typedef struct s_env_table
{
	t_table	*table;
	char	*(*get)(t_table *self, char *key);
    int		(*set)(t_table **self, char *str);
	void	*(*clear)(struct s_env_table *env_table);
} t_env_table;

t_env_table *table_init(char **envp);
#endif
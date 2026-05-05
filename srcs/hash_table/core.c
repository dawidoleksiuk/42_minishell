/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:26:53 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/05 08:16:12 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "hash_table_internal.h"

void	free_list(t_list *list, int flag)
{
	t_list	*next;

	next = list->next[SORTED];
	free(list->next);
	free(list->prev);
	free(list->key);
	free(list->value);
	free(list);
	if (next && flag)
		return (free_list(next, flag));
}

void	*free_table(t_env_table *env_table)
{
	if (env_table->table->sorted_list)
		free_list(env_table->table->sorted_list, ALL);
	if (env_table->table->env)
		free_list(env_table->table->env, ALL);
	free(env_table->table->nodes);
	free(env_table->table);
	free(env_table);
	return (NULL);
}

static int	copy_envp(t_table **table, char **envp)
{
	char	*str;
	char	*key;
	char	*value;

	while (envp && *envp)
	{
		str = ft_strdup(*envp);
		if (!str || seperate_string(str, &key, &value)
			|| table_add(table, key, value))
			return (1);
		envp++;
	}
	return (0);
}

static t_table	*table_alloc(void)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (NULL);
	table->nodes = ft_calloc(VARIABLES_HASH_BUCKETS, sizeof(t_list *));
	if (!table->nodes)
		return (free(table), NULL);
	return (table);
}

t_env_table	*table_init(char **envp)
{
	t_env_table	*env_table;

	env_table = ft_calloc(1, sizeof(t_env_table));
	if (!env_table)
		return (NULL);
	env_table->table = table_alloc();
	if (env_table->table)
	{
		if (!copy_envp(&env_table->table, envp))
			sort(&env_table->table);
		else
			return (free_table(env_table));
	}
	else
		return (free(env_table), NULL);
	env_table->get = &get;
	env_table->set = &set;
	env_table->del = &del;
	env_table->clear = &free_table;
	env_table->display = &display;
	return (env_table);
}

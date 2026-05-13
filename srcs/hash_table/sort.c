/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:41:28 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/13 11:11:18 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table_internal.h"

void	insert_sorted_list(t_list **head, t_list *new_node)
{
	t_list	*current;

	if (!new_node)
		return ;
	new_node->next[SORTED] = NULL;
	new_node->prev[SORTED] = NULL;
	if (!*head || ft_strisless(new_node->key, (*head)->key, 0))
	{
		new_node->next[SORTED] = *head;
		if (*head)
			(*head)->prev[SORTED] = new_node;
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next[SORTED]
		&& ft_strismore(new_node->key, current->next[SORTED]->key, 0))
		current = current->next[SORTED];
	new_node->next[SORTED] = current->next[SORTED];
	if (current->next[SORTED])
		current->next[SORTED]->prev[SORTED] = new_node;
	current->next[SORTED] = new_node;
	new_node->prev[SORTED] = current;
}

void	sort(t_table **table)
{
	t_list	*env;
	t_list	*env_next;

	if (!table || !*table)
		return ;
	env = (*table)->env;
	while (env)
	{
		env_next = env->next[SORTED];
		insert_sorted_list(&(*table)->sorted_list, env);
		env = env_next;
	}
	(*table)->env = NULL;
}

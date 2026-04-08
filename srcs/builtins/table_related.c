/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:54:00 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/08 19:28:11 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_env(t_list **table)
// {
// 	display_table(table, "", 0, 0);
// }

void	ft_unset(t_env_table **table, char **args)
{
	while (*args)
	{
		(*table)->del(&(*table)->table, *args);
		args++;
	}	
}

// void	ft_export(t_exec_info *exec, t_list **table, char **args)
// {
// 	ssize_t	i;
// 	t_list	*node;
// 	char	*key;
// 	char	*value;

// 	if (!args[1])
// 	{
// 		display_table(table, "declare -x ", 1, 1);
// 		return ;
// 	}
// 	i = table_get_i(args[1][0]);
// 	if (i < 0)
// 	{
// 		ft_putstr_fd("minishell: export: '", 2);
// 		ft_putstr_fd(args[1], 2);
// 		ft_putstr_fd("': not a valid identifier\n", 2);
// 		return ;
// 	}
// 	if (table_sep_string(args[1], &key, &value))
// 	{	
// 		if (key)
// 			free(key);
// 		return (clean_exec(exec, "malloc failed\n", 1, key));
// 	}
// 	node = table_find_node(table, key);
// 	if (!node)
// 	{
// 		if (table_add(&(table[i]), key, value))
// 			return (clean_exec(exec, "malloc failed\n", 1, key));
// 	}
// 	else
// 	{
// 		if (node->value)
// 			free(node->value);
// 		free(key);
// 		node->value = value;
// 	}
// }
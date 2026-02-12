/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:51:11 by alusnia           #+#    #+#             */
/*   Updated: 2026/02/12 13:12:51 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_envar **envar, char *path)
{
	char	*temp;

	temp = ft_strjoin("/", path);
	if (!temp)
		return (1);
	path = temp;
	temp = ft_strjoin((*envar)->curr_dir, path);
	if (!temp)
		return (1);
	if (chdir(temp) == -1)
		perror("cd");
	else
	{
		free((*envar)->curr_dir);
		(*envar)->curr_dir = temp;
		return (0);
	}
	return (1);
}

int	ft_pwd(t_envar **envar)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
		return (0);
	}
	else if (envar && *envar && (*envar)->curr_dir)
	{
		ft_printf("%s\n", (*envar)->curr_dir);
		return (0);
	}
	perror("pwd");
	return (1);
}

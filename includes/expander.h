/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:47:58 by doleksiu          #+#    #+#             */
/*   Updated: 2026/05/10 11:22:43 by doleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H	
# define EXPANDER_H

typedef struct s_data	t_data;

typedef struct s_exp_data
{
	int		i;
	char	c;
	int		start;
	int		status;
	int		key_len;
}	t_exp_data;

void	expander(t_data *data);
void	append_dollar(t_data *data, t_exp_data *exp, char *content, char **res);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:52:52 by alusnia           #+#    #+#             */
/*   Updated: 2026/04/22 19:53:21 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdlib.h>
# include "minishell.h"

# define IS_CHILD 0

//executor.c
int				check_for_built_ins(t_data *data, t_cmd *cmd);
//parent.c
void			check_out_children(t_exec_info *exec_info,
					int *exit_code);
unsigned char	translate_status(pid_t data_pid, pid_t pid,
					int status, unsigned char error);
t_exec_info		*give_birth(t_data *data, t_exec_info *exec_info, t_cmd *cmd);
//child.c
void			set_up_child(t_data *data, t_exec_info *exec_info, t_cmd *cmd);
void			do_your_job(t_data *data, t_exec_info *exec_info, t_cmd *cmd);

#endif
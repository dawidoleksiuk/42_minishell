/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:52:52 by alusnia           #+#    #+#             */
/*   Updated: 2026/05/10 14:47:44 by alusnia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
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

//child_utils.c
void			iter_catalogs(t_exec_info *exec_info);
char			**filtr_cmd(t_cmd *cmd);
char			*check_path(t_exec_info *exec_info, char **args);
t_exec_info		*check_catalogs(t_exec_info *exec_info,
					char *path, char *f_name);
int				check_for_directory(char *path);

//exit.c
void			clean_exec(t_exec_info *exec_info, char *msg,
					int exit_code, void *bonus);
void			clean_envars(t_envar *envars);
void			clean_exit_executor(t_exec_info *exec_info);

#endif
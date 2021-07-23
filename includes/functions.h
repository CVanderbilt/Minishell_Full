/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:41:59 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:29:30 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "minishell.h"

int		set_ret(t_shell *s, int ret);
void	*free_argv(char **argv);

int		ms_pwd(t_shell *data);
int		ms_echo(t_shell *data);
int		ms_cd(t_shell *data);
int		ms_export(t_shell *data);
int		ms_unset(t_shell *data);
int		ms_env(t_shell *data);
int		ms_exit(t_shell *data);
int		ms_test(t_shell *data);
int		ms_exec(t_shell *data);

#endif
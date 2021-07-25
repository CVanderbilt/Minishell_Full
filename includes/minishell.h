/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:53:40 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:31:51 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "utils.h"
# include "env_set.h"
# include "cmd.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "utils.h"
# include "env_set.h"

#include "minierrors.h"

# define CMD_SIZE 7

typedef struct s_cmd
{
	char	*cmds[CMD_SIZE + 1];
	void	*ms_cmds[CMD_SIZE + 1];
	void	*exec;
	int		argc;
	char	**argv;
	char	reds;
}				t_cmd;

typedef struct s_shell
{
	unsigned int	ret;
	int				fd;
	int				pipe_read;
	int				pipe_write;
	int				prev_pipe_read;
	char			*userpromt;
	int				last_status;
	int				forked;
	int				isquoted;
	int				stdin_save;
	int				stdout_save;
	int				stderr_save;
	int				i_hijos;
	int				pid;
	int				is_child;
	int				pos;
	t_cmd			*cmd;
	t_env			*env;
	t_args			*args;
	t_redir_data	r;
	int				exit_code;
}				t_shell;

typedef struct s_ac
{
	int		j;
	int		flag;
	char	buff[2];
	char	*tmp;
	t_args	*args;
	int		is_red;
}	t_ac;

int				get_next_line(char **line);
void			statuslog(t_shell *shell);//temporal para tests
int				isspecialchar(const char *line, int j);
int				isquoted(t_shell *shell, const char *line, int pos, char **dst);
int				reset_argv(t_shell *shell);
int				parser(t_shell *shell, char **line, int pos);
int				arg_counter(t_shell *shell, const char *line, int pos);
int				reds_counter(t_shell *shell, const char *line, int j);
void			*get_cmd(t_shell *shell);
int				piped_execution(t_shell *shell,
void 			*(*ms_cmd)(t_shell*), char *line);
char			*unnamed(t_shell *shell, const char *line, int i, int pos);
int				get_var(t_shell *shell, const char *line, char **dst, int pos);
int				apply_redirections(t_shell *s, t_args **list);
int				main_loop(t_shell *shell, const char *line, t_ac *a);

int				is_cmd_sep(char c);
int				is_cmd_red(char c);
int				is_preserved(char c);

int				check_path_is_exec(const char *path);
int				isAbsolute(const char *path);
char			*get_full_path(char *path);

int				init_shell(
					t_shell *shell, int argc, char *argv[], const char **envp);
int				init_commands(t_shell *shell);

int				if_helper(const char *line, t_ac *a, int option);
#endif

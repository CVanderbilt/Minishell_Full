/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:39:02 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:28:18 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_SET_H
# define ENV_SET_H

typedef struct s_env
{
	char	*key;
	char	*value;
	void	*next;
}				t_env;

int					env_add_safe(t_env *start, const char *key,
						const char *value);
t_env				*env_init(const char **str);
void				env_free(t_env **start);
void				env_delete(t_env **env, const char *key);
char				*env_get(t_env *start, const char *key);
void				env_add(t_env *start, t_env *e);
t_env				*new_env(const char *str);
t_env				*new_env2(const char *key, const char *value);
unsigned int		env_size(t_env *start);
char				**env_raw(t_env *start);
int					env_sorted_display_all(t_env *start);

#endif
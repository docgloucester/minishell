/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:51:40 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 23:26:00 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARENV_H
# define VARENV_H
# include <stdlib.h>
# include <stdio.h>
# include "../minishell.h"

typedef struct s_envitem {
	int			value_num;
	char		*name;
	char		**value;
	void		*next;
}				t_envitem;

typedef struct s_varenv {
	int			count;
	char		bin_return;
	char		**env_to_str;
	t_envitem	*envtab;
}				t_varenv;

int				search_char(char *str, char c, int returnlength);
int				find_name(t_envitem *ei, char *src);
int				find_content(t_envitem *ei, char *src);
int				varenv_extract(t_varenv *ve, char *src);
t_varenv		varenv_construct(char **src);
int				count_varenv_occ(char *src);
int				extract_content(char **str, char *src);
void			envitem_kill(t_envitem *ei);
void			varenv_kill(t_varenv *ve);
int				push_envitem(t_varenv *ve, char *src);
int				pop_envitem(t_varenv *ve, char *str);
char			**env_to_str(t_varenv *ve);
void			kill_env_to_str(char **ets);
char			**var_value_finder(t_varenv *ve, char *var_name, char malloc_str);
void			builtin_env(t_varenv *ve);
void			builtin_export(t_varenv *ve, int argc, char **args);
void			builtin_unset(t_varenv *ve, int argc, char **args);

#	endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:49:13 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/27 10:28:36 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../_libft/libft.h"
# include "exec/exec.h"
# include "varenv/varenv.h"
# include "builtin/builtin.h"
# include "parser/parser.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>

typedef struct s_minishell
{
	t_varenv	ve;
	t_execdata	*ed;
}				t_minishell;

int		error_handler(char *cmd, char *arg, int retval);
int		error_syntax_handler(char *str, int len, int retval);
int		error_handler_p(char *cmd, int retval);
int		ccon_to_exec(t_cmdcontent *ccon_full, struct s_minishell *m);
int		first_parser(t_minishell *m, char *line);
int		second_parser(t_execdata *d, t_varenv *ve);
int		var_resolver(char **cmd, t_varenv *ve);
int		var_concat(char *current, char **new, t_varenv *ve, int next_var);

#endif
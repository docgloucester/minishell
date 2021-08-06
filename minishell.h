/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:49:13 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/06 16:20:25 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "_libft/libft.h"
# include "exec/exec.h"
# include "varenv/varenv.h"
# include "builtin/builtin.h"
# include "cp/command_parsing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>

typedef struct s_minishell
{
	char		nameofshell[30];
	t_varenv	ve;
	t_execdata	*ed;
}				t_minishell;

int		error_handler(char *cmd, char *arg, int retval);

# endif
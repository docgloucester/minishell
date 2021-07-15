/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:49:13 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 23:01:25 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "_libft/libft.h"
# include "exec/exec.h"
# include "varenv/varenv.h"
# include "explorer/explorer.h"

typedef struct s_minishell
{
	char		nameofshell[30];
	t_varenv	ve;
	t_execdata	*ed;
}				t_minishell;

# endif
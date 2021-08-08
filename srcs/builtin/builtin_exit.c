/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:37:42 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/05 17:24:15 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int		builtin_exit(void *minishell)
{
	t_minishell *m = (t_minishell *)minishell;
	printf("exit\n");
	varenv_kill(&m->ve);
	exec_killer(m->ed);
	exit(EXIT_SUCCESS);
	return (0);
}
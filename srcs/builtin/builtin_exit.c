/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:37:42 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/11 15:15:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_exit(void *minishell)
{
	t_minishell	*m;

	m = minishell;
	printf("exit\n");
	varenv_kill(&m->ve);
	exec_killer(m->ed);
	exit(EXIT_SUCCESS);
	return (0);
}

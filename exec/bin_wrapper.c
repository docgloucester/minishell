/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:29:34 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/16 15:06:13 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	bin_wrapper(t_execdata *d, t_varenv *ve)
{
	if (var_setter(d) == -1)
		return (-1);
	if (d->pid)
	{
		pipe_setter(d, 0);
		if (d->pipe_on)
			if (cmd_dispatcher(d->next, ve) < 0)
				return (-1);
		if (!d->pipe_on)
			if (cmd_dispatcher(NULL, ve) < 0)
				return (-1);
		waitpid(d->pid, &d->return_v, 0);
		ft_close(d->pipes, 2);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		if (pipe_setter(d, 1) == -1)
			exit(EXIT_FAILURE);
		if (execve(d->cmd[0], d->cmd, ve->env_to_str) == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}

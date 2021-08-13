/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:01:29 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/13 19:35:14 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	builtin_wrapper(t_execdata *d, t_varenv *ve)
{
	signal(SIGINT, SIG_DFL);
	if (d->pipe_on)
		if (pipe(d->pipes) == -1)
			return (error_handler(NULL, d->cmd[0], -1));
	if (d->prec && d->prec->pipe_on)
		ft_close(&d->prec->pipes[0], 1);
	exec_cleaner(ve->minishell_var, &d);
	d->return_v = builtin_dispatcher(d, ve) << 8;
	if (d->pipe_on)
		ft_close(&d->pipes[1], 1);
	if (d->pipe_on)
		if (cmd_dispatcher(d->next, ve) < 0)
			return (-1);
	if (!d->pipe_on)
		cmd_dispatcher(NULL, ve);
	ft_close(d->pipes, 2);
	return (0);
}

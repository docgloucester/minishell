/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:23:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 12:08:22 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	cmd_dispatcher(t_execdata *d, t_varenv *ve)
{
	if (d && d->type == BINARY)
		if (bin_wrapper(d, ve) < 0)
			return (-1);
	if (d && (d->type == OUTPUT || d->type == OUTPUT_D))
		if (export_wrapper(d, ve) < 0)
			return (-1);
	if (d && d->type == INPUT)
		if (import_wrapper(d, ve) < 0)
			return (-1);
	if (d && d->type == INPUT_D)
		if (interactive_wrapper(d, ve) < 0)
			return (-1);
	return (0);
}

int	exec_ret(t_execdata *d)
{
	t_execdata *ret;

	ret = NULL;
	while (d && d->pipe_on)
	{
		if (WIFSIGNALED(d->return_v) && WTERMSIG(d->return_v) == 2)
			return (130);
		if (d->type == BINARY || d->type == BUILTIN || ((d->type == OUTPUT || \
		d->type == OUTPUT_D || d->type == INPUT) && WEXITSTATUS(d->return_v)))
			ret = d;
		d = d->next;
	}
	if (WIFSIGNALED(d->return_v) && WTERMSIG(d->return_v) == 2)
		return (130);
	if (d->type == BINARY || d->type == BUILTIN || ((d->type == OUTPUT || \
	d->type == OUTPUT_D || d->type == INPUT) && WEXITSTATUS(d->return_v)))
		ret = d;
	return (WEXITSTATUS(ret->return_v));
}

int	exec_loop(t_execdata *d, t_varenv *ve)
{
	t_execdata	*first;
	pid_t		pid;
	int			status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	while (d)
	{
		first = d;
		status = cmd_dispatcher(d, ve);
		if (status == -1)
			printf("error\n");
		while (d && d->pipe_on)
			d = d->next;
		d = d->next;
	}
	signal(SIGINT, SIG_DFL);
	return (exec_ret(first));
}

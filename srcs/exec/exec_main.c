/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:23:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/12 16:17:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	resolution(t_execdata *d, t_varenv *ve)
{
	// fonction qui resout toutes les variables
	// fonction qui trim les guillemets et qui enlève les blackslashs
	// fonction qui enlève les nulls dans la chaine
	// fonction qui met builtin a la place de bin si il faut
}

int	cmd_dispatcher(t_execdata *d, t_varenv *ve)
{
	// fonction resolution variables & determination type BIN/BUILTIN
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
		if (interactive_wrapper(d, ve, 0) < 0)
			return (-1);
	if (d && d->type == BUILTIN)
		if (builtin_wrapper(d, ve) < 0)
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
		if (WIFSIGNALED(d->return_v) && WTERMSIG(d->return_v) == 3)
			return (131);
		if (d->type == BINARY || d->type == BUILTIN || ((d->type == OUTPUT || \
		d->type == OUTPUT_D || d->type == INPUT) && WEXITSTATUS(d->return_v)))
			ret = d;
		d = d->next;
	}
	if (WIFSIGNALED(d->return_v) && WTERMSIG(d->return_v) == 2)
		return (130);
	if (WIFSIGNALED(d->return_v) && WTERMSIG(d->return_v) == 3)
		return (131);
	if (d->type == BINARY || d->type == BUILTIN || ((d->type == OUTPUT || \
	d->type == OUTPUT_D || d->type == INPUT) && WEXITSTATUS(d->return_v)))
		ret = d;
	return (WEXITSTATUS(ret->return_v));
}

int	exec_loop(t_execdata *d, t_varenv *ve)
{
	t_execdata	*first;
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
		if (exec_ret(first) == 131)
			printf("Quit (core dumped)\n");
	}
	signal(SIGINT, SIG_DFL);
	return (exec_ret(first));
}

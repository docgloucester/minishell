/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:23:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/16 15:10:06 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	signo(int signal)
{
	return ;
}

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

int	exec_ret(t_execdata *d, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		return (130);
	return (WEXITSTATUS(status));
}

int	exec_loop(t_execdata *d, t_varenv *ve)
{
	pid_t		pid;
	int			status;

	status = 0;
	signal(SIGINT, signo);
	while (d)
	{
		status = cmd_dispatcher(d, ve);
		if (status == -1)
			printf("error\n");
		while (d && d->pipe_on)
			d = d->next;
		d = d->next;
	}
	return (exec_ret(d, status));
}

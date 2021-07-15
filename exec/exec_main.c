/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:23:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 22:59:40 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	cmd_dispatcher(t_execdata *d, t_varenv *ve)
{
	if (d && d->type == BINARY)
		if (bin_wrapper(d, ve) == -1)
			return (-1);
	if (d && (d->type == OUTPUT || d->type == OUTPUT_D))
		if (export_wrapper(d, ve) == -1)
			return (-1);
	if (d && d->type == INPUT)
		if (import_wrapper(d, ve) == -1)
			return (-1);
	if (d && d->type == INPUT_D)
		if (interactive_wrapper(d, ve) == -1)
			return (-1);
	return (0);
}

int	exec_ret(int status)
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
	while (d && WIFEXITED(status))
	{
		pid = fork();
		if (pid == -1)
			return (-1); // error: impossible de créer l'environnement d'éxecution.
		if (pid)
			waitpid(pid, &status, 0);
		else
		{
			signal(SIGINT, SIG_DFL);
			if (cmd_dispatcher(d, ve) == -1)
				exit(EXIT_FAILURE);
			exit(find_ret_value(d) >> 8 & 0xFF);
		}
		while (d && d->pipe_on)
			d = d->next;
		d = d->next;
	}
	return (exec_ret(status));
}

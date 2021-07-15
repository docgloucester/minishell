/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:23:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 07:37:35 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"exec.h"

int	cmd_dispatcher(t_execdata *d, char **env)
{
	if (d && d->type == BINARY)
		if (bin_wrapper(d, env) == -1)
			return (-1);
	if (d && (d->type == OUTPUT || d->type == OUTPUT_D))
		if (export_wrapper(d, env) == -1)
			return (-1);
	if (d && d->type == INPUT)
		if (import_wrapper(d, env) == -1)
			return (-1);
	if (d && d->type == INPUT_D)
		if (interactive_wrapper(d, env) == -1)
			return (-1);
	return (0);
}

int	exec_ret(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		return (130);
	return (WEXITSTATUS(status));
}

int	exec_loop(t_execdata *d, char **env)
{
	pid_t		pid;
	int			status;

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
			if (cmd_dispatcher(d, env) == -1)
				exit(EXIT_FAILURE);
			exit(find_ret_value(d) >> 8 & 0xFF);
		}
		while (d && d->pipe_on)
			d = d->next;
		d = d->next;
	}
	return (exec_ret(status));
}

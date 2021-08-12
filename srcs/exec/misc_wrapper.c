/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:30:24 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/12 18:11:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

void	ft_close(int *fd, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (fd[i])
		{
			close(fd[i]);
			fd[i] = 0;
		}
		i++;
	}
}

int	ft_kill(t_execdata *d, int sig, int retval)
{
	if (d->prec)
	{
		kill(d->prec->pid, sig);
		d->prec->return_v = 40;
	}
	return (retval);
}

int	var_setter(t_execdata *d, t_varenv *ve)
{
	exec_cleaner(ve->minishell_var, &d);
// debug_execdata(d);
	if (d->type == BINARY && search_in_path(d, ve) == -1)
		return(error_handler(NULL, d->cmd[0], -1));
	if (d->pipe_on)
		if (pipe(d->pipes) == -1)
			return(error_handler(NULL, d->cmd[0], -1));
	d->pid = fork();
	if (d->pid == -1)
		return(error_handler(NULL, d->cmd[0], -1));
	return (0);
}

int	pipe_setter(t_execdata *d, int child)
{
	if (d->prec && d->prec->pipe_on)
	{
		if (d->type != INPUT_D && child && \
		(dup2(d->prec->pipes[0], STDIN_FILENO) == -1))
			return(error_handler(NULL, d->cmd[0], -1));
		ft_close(&d->prec->pipes[0], 1);
	}
	if (d->pipe_on)
	{
		if (child && (dup2(d->pipes[1], STDOUT_FILENO) == -1))
			return(error_handler(NULL, d->cmd[0], -1));
		if (child)
			ft_close(&d->pipes[0], 1);
		ft_close(&d->pipes[1], 1);
	}
	return (0);
}

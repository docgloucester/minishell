/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:30:24 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/03 19:11:08 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

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

int		var_setter(t_execdata *d)
{
	if (d->pipe_on)
		if (pipe(d->pipes) == -1)
		{
			d->error = PIPE;
			return (-1);
		}
	d->pid = fork();
	if (d->pid == -1)
	{
		d->error = FORK;
		return (-1);
	}
	return (0);
}

int		pipe_setter(t_execdata *d, int child)
{
	if (d->prec && d->prec->pipe_on)
	{
		if (child && (dup2(d->prec->pipes[0], STDIN_FILENO) == -1))
		{
			d->error = DUP;
			return (-1);
		}
		close(d->prec->pipes[0]);
	}
	if (d->pipe_on)
	{
		if (child && (dup2(d->pipes[1], STDOUT_FILENO) == -1))
		{
			d->error = DUP;
			return (-1);
		}
		if (child)
			close(d->pipes[0]);
		close(d->pipes[1]);
	}
	return (0);
}

int		find_ret_value(t_execdata *d)
{
	int		ret;

	ret = 0;
	while (d && d->pipe_on)
	{
		if (d->type == BINARY || d->type == BUILTIN)
			ret = d->return_v;
		d = d->next;
	}
	if (d->type == BINARY || d->type == BUILTIN)
		ret = d->return_v;
	return (ret);
}
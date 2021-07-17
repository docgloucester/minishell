/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:30:24 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 10:42:09 by nouchata         ###   ########.fr       */
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

int	var_setter(t_execdata *d)
{
	if (d->pipe_on)
		if (pipe(d->pipes) == -1)
			return(error_handler("bash", d->cmd[0], -1));
	d->pid = fork();
	if (d->pid == -1)
		return(error_handler("bash", d->cmd[0], -1));
	return (0);
}

int	pipe_setter(t_execdata *d, int child)
{
	if (d->prec && d->prec->pipe_on)
	{
		if (d->type != INPUT_D && child && \
		(dup2(d->prec->pipes[0], STDIN_FILENO) == -1))
			return(error_handler("bash", d->cmd[0], -1));
		ft_close(&d->prec->pipes[0], 1);
	}
	if (d->pipe_on)
	{
		if (child && (dup2(d->pipes[1], STDOUT_FILENO) == -1))
			return(error_handler("bash", d->cmd[0], -1));
		if (child)
			ft_close(&d->pipes[0], 1);
		ft_close(&d->pipes[1], 1);
	}
	return (0);
}

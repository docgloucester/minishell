/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:12:27 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/13 21:12:20 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	close_fd(int fd)
{
	if (fd)
		close(fd);
	return (0);
}

int	exec_builder(t_execdata **d, char **cmd, t_exectype type, char pipe)
{
	t_execdata	*new;
	t_execdata	*current;

	new = malloc(sizeof(t_execdata) * 1);
	if (!new)
		return (error_handler(NULL, NULL, -1));
	current = *d;
	while (current && current->next)
		current = current->next;
	new->type = type;
	new->cmd = cmd;
	new->pipes[0] = 0;
	new->pipes[1] = 0;
	ft_close(new->pipes, 2);
	new->pipe_on = pipe;
	new->pid = 0;
	new->prec = NULL;
	new->return_v = 0;
	if (current)
		new->prec = current;
	new->next = NULL;
	if (current)
		current->next = new;
	else
		*d = new;
	return (0);
}

int	exec_killer(t_execdata *d)
{
	int			i;
	t_execdata	*next;

	next = NULL;
	while (d)
	{
		i = 0;
		while (d->cmd && d->cmd[i])
		{
			free(d->cmd[i]);
			i++;
		}
		free(d->cmd);
		if (d->pid)
			kill(d->pid, SIGTERM);
		ft_close(d->pipes, 2);
		next = d->next;
		free(d);
		d = next;
	}
	return (0);
}

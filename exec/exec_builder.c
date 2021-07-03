/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:12:27 by nouchata          #+#    #+#             */
/*   Updated: 2021/06/15 21:48:00 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

int		close_fd(int fd)
{
	if (fd)
		close(fd);
	return (0);
}

int		exec_builder(t_execdata **d, char **cmd, t_exectype type, char pipe)
{
	t_execdata *new;
	t_execdata *current;

	new = malloc(sizeof(t_execdata) * 1);
	if (!new)
		return (-1);
	current = *d;
	while (current && current->next)
		current = current->next;
	new->type = type;
	new->cmd = cmd;
	new->pipes[0] = 0;
	new->pipes[1] = 0;
	new->pipe_on = pipe;
	new->error = NO_ERROR;
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
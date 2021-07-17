/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:12:27 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 15:47:56 by nouchata         ###   ########.fr       */
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
		return(error_handler(NULL, NULL, -1));
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

int	exec_killer(t_execdata *d)
{
	t_execdata *next;

	next = NULL;
	while (d)
	{
		ft_close(d->pipes, 2);
		//kill_env_to_str(d->cmd);
		next = d->next;
		free(d);
		d = next;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:49:55 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 07:44:10 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"exec.h"

int	export_fd(t_execdata *d, int *fd, int *ret)
{
	if (d->type == OUTPUT)
		*fd = open(d->cmd[0], O_WRONLY | O_CREAT, 0664);
	else
		*fd = open(d->cmd[0], O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*fd == -1)
	{
		d->error = OPEN;
		return (-1);
	}
	*ret = 1;
	return (0);
}

int	export_loop(t_execdata *d)
{
	int		fd;
	int		ret;
	char	buffer[30];

	export_fd(d, &fd, &ret);
	while (ret)
	{
		ft_memset(buffer, 0, 30);
		ret = read(STDIN_FILENO, buffer, 29);
		if (ret == -1)
		{
			d->error = READ;
			return (-1);
		}
		if (d->pipe_on)
			write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		write(fd, buffer, ft_strlen(buffer));
	}
	close(STDOUT_FILENO);
	close(fd);
	return (0);
}

int	export_wrapper(t_execdata *d, char **env)
{
	if (var_setter(d) == -1)
		return (-1);
	if (d->pid)
	{
		pipe_setter(d, 0);
		if (d->pipe_on)
			if (cmd_dispatcher(d->next, env) == -1)
				return (-1);
		if (!d->pipe_on)
			if (cmd_dispatcher(NULL, env) == -1)
				return (-1);
		waitpid(d->pid, &d->return_v, 0);
		ft_close(d->pipes, 2);
	}
	else
	{
		if (pipe_setter(d, 1) == -1)
			exit(EXIT_FAILURE);
		if (export_loop(d) == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}

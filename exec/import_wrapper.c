/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:50:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/16 15:07:13 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	interactive_loop(t_execdata *d, int fdout)
{
	char	*str;

	write(fdout, "> ", 2);
	while (get_next_line(STDIN_FILENO, &str))
	{
		if (!ft_strncmp(d->cmd[0], str, 0))
			return (0);
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
		write(fdout, "> ", 2);
		free(str);
		str = NULL;
	}
	free(str);
	return (0);
}

int	import_loop(t_execdata *d)
{
	int		fd;
	int		ret;
	char	buffer[100];

	fd = open(d->cmd[0], O_RDONLY);
	if (fd == -1)
		return (-1); // intégrer un système d'erreurs cf si le fichier n'a pas les droits
	ret = 1;
	while (ret)
	{
		ft_memset(buffer, 0, 100);
		ret = read(fd, buffer, 99);
		if (ret == -1)
		{
			d->error = READ;
			return (-1);
		}
		write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	}
	return (0);
}

int	import_wrapper(t_execdata *d, t_varenv *ve)
{
	if (var_setter(d) == -1)
		return (-1);
	if (d->pid)
	{
		pipe_setter(d, 0);
		if (d->pipe_on)
			if (cmd_dispatcher(d->next, ve) < 0)
				return (-1);
		if (!d->pipe_on)
			if (cmd_dispatcher(NULL, ve) < 0)
				return (-1);
		waitpid(d->pid, &d->return_v, 0);
		ft_close(d->pipes, 2);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		if (pipe_setter(d, 1) == -1)
			exit(EXIT_FAILURE);
		if (import_loop(d) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	interactive_wrapper(t_execdata *d, t_varenv *ve)
{
	int		fdout;

	if (var_setter(d) == -1)
		return (-1);
	if (d->pid)
	{
		pipe_setter(d, 0);
		waitpid(d->pid, &d->return_v, 0);
		if (d->pipe_on)
			if (cmd_dispatcher(d->next, ve) < 0)
				return (-1);
		if (!d->pipe_on)
			if (cmd_dispatcher(NULL, ve) < 0)
				return (-1);
		ft_close(d->pipes, 2);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		fdout = dup(STDOUT_FILENO);
		if (pipe_setter(d, 1) == -1)
			exit(EXIT_FAILURE);
		if (interactive_loop(d, fdout) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

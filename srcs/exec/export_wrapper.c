/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:49:55 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 15:48:24 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	export_fd(t_execdata *d, int *fd, int *ret)
{
	if (d->type == OUTPUT)
		*fd = open(d->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		*fd = open(d->cmd[0], O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (*fd == -1)
		return (error_handler(NULL, d->cmd[0], -1));
	*ret = 1;
	return (0);
}

int	export_loop(t_execdata *d)
{
	int		fd;
	int		ret;
	char	buffer[30];

	if (!d->cmd || !d->cmd[0])
		return (error_handler_p("ambiguous redirect", -1));
	if (export_fd(d, &fd, &ret) == -1)
		return (-1);
	while (ret)
	{
		ft_memset(buffer, 0, 30);
		ret = read(STDIN_FILENO, buffer, 29);
		if (ret == -1)
		{
			close(fd);
			return (error_handler(NULL, d->cmd[0], -1));
		}
		if (d->pipe_on)
			write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		write(fd, buffer, ft_strlen(buffer));
	}
	close(STDOUT_FILENO);
	close(fd);
	return (0);
}

int	export_wrapper(t_execdata *d, t_varenv *ve)
{
	if (var_setter(d, ve) == -1)
		return (-1);
	if (d->pid)
	{
		pipe_setter(d, 0);
		if (d->pipe_on)
			if (cmd_dispatcher(d->next, ve) < 0)
				return (-1);
		if (!d->pipe_on)
			cmd_dispatcher(NULL, ve);
		waitpid(d->pid, &d->return_v, 0);
		ft_close(d->pipes, 2);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pipe_setter(d, 1) == -1)
			fork_exit(ve->minishell_var, EXIT_FAILURE);
		if (export_loop(d) == -1)
			fork_exit(ve->minishell_var, ft_kill(d, SIGTERM, EXIT_FAILURE));
		fork_exit(ve->minishell_var, EXIT_SUCCESS);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:35:20 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/12 18:59:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	print_builtin(t_execdata *d, char *str)
{
	if (d->pipe_on)
		write(d->pipes[1], str, ft_strlen(str));
	else
		write(1, str, ft_strlen(str));
	return (0);
}

int	builtin_dispatcher(t_execdata *d, t_varenv *ve)
{
	int		i;

	i = 0;
	if (d && !ft_strncmp(d->cmd[0], "env", 0))
		return (builtin_envc(d, ve));
	if (d && !ft_strncmp(d->cmd[0], "export", 0))
		i = builtin_export(d, ve);
	if (d && !ft_strncmp(d->cmd[0], "unset", 0))
		i = builtin_unset(d, ve);
	if (d && !ft_strncmp(d->cmd[0], "cd", 0))
		return (builtin_cd(d));
	if (d && !ft_strncmp(d->cmd[0], "echo", 0))
		return (builtin_echo(d));
	if (d && !ft_strncmp(d->cmd[0], "exit", 0))
		return (builtin_exit(ve->minishell_var));
	if (d && (!ft_strncmp(d->cmd[0], "export", 0) || \
	!ft_strncmp(d->cmd[0], "unset", 0)))
	{
		kill_env_to_str(ve->env_to_str);
		ve->env_to_str = env_to_str(ve);
		return (i);
	}
	return (0);
}

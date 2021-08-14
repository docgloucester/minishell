/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:01:01 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/12 19:46:37 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_echo_check_option(char *str)
{
	int		i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_execdata *d)
{
	char	c;
	int		i;

	i = 1;
	c = 1;
	if (builtin_echo_check_option(d->cmd[1]))
		c = 0;
	if (!c)
		i++;
	while (d->cmd[i])
	{
		print_builtin(d, d->cmd[i]);
		if (d->cmd[i + 1])
			print_builtin(d, " ");
		i++;
	}
	if (c)
		print_builtin(d, "\n");
	return (0);
}

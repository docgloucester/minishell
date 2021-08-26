/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:05:06 by marvin            #+#    #+#             */
/*   Updated: 2021/08/25 16:38:02 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	error_handler(char *cmd, char *arg, int retval)
{
	write(2, "bâche: ", 9);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	perror("");
	return (retval);
}

int	error_handler_p(char *cmd, int retval)
{
	write(2, "bâche: ", 9);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
	}
	return (retval);
}

int	error_syntax_handler(char *str, int len, int retval)
{
	if (!str)
	{
		write(2, "bâche: syntax error\n", 22);
		return (retval);
	}
	if (!len)
		len = ft_strlen(str);
	write(2, "bâche: syntax error near `", 28);
	write(2, str, len);
	write(2, "\'\n", 2);
	return (retval);
}
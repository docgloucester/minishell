/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:05:06 by marvin            #+#    #+#             */
/*   Updated: 2021/08/25 14:57:31 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	error_handler(char *cmd, char *arg, int retval)
{
	write(2, "bash: ", 6);
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

int	error_syntax_handler(char *str, int len, int retval)
{
	if (!str)
	{
		write(2, "bash: syntax error", 18);
		return (retval);
	}
	if (!len)
		len = ft_strlen(str);
	write(2, "bash: syntax error near `", 25);
	write(2, str, len);
	write(2, "\'\n", 2);
	return (retval);
}
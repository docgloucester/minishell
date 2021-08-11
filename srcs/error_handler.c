/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:05:06 by marvin            #+#    #+#             */
/*   Updated: 2021/08/11 15:06:26 by marvin           ###   ########.fr       */
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

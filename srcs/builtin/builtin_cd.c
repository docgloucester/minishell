/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:34:12 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/08 15:37:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_cd(t_execdata *d)
{
	int		ret;

	ret = 0;
	if (!d->cmd[1] || !ft_strlen(d->cmd[1]))
		return (0);
	ret = chdir(d->cmd[1]);
	if (ret == -1)
		return (error_handler("cd", d->cmd[1], 1));
	return (0);
}
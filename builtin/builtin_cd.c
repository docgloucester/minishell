/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:34:12 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 17:19:09 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_cd(t_execdata *d, t_varenv *ve)
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
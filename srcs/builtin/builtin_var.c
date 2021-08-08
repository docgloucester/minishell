/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:52:19 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/20 18:34:53 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_envc(t_execdata *d, t_varenv *ve)
{
	int		i;

	i = 0;
	while (ve->env_to_str[i])
	{
		print_builtin(d, ve->env_to_str[i]);
		print_builtin(d, "\n");
		i++;
	}
	return (0);
}

int	builtin_unset(t_execdata *d, t_varenv *ve)
{
	if (!d->cmd[1] || !ft_strlen(d->cmd[1]))
		return (0);
	pop_envitem(ve, d->cmd[1], 0);
	return (0);
}

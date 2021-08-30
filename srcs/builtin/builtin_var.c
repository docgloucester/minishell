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
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (d->cmd[++i])
	{
		if (is_invalid_ident(d->cmd[i], 0))
		{
			write(2, "bâche: export: `", 17);
			write(2, d->cmd[i], ft_strlen(d->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			ret = 1;
		}
		else
			pop_envitem(ve, d->cmd[i], 0);
	}
	return (ret);
}

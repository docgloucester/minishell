/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:52:19 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 17:31:14 by nouchata         ###   ########.fr       */
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
	pop_envitem(ve, d->cmd[1]);
	return (0);
}

int	export_namechecker(char *src)
{
	int		i;

	i = 0;
	if (!ft_strlen(src) || src[i] == '=')
		return (2);
	while (src[i] && src[i] != '=')
	{
		if (src[i] == ' ')
			return (2);
		i++;
	}
	if (!src[i])
		return (1);
	return (0);
}

int	builtin_export(t_execdata *d, t_varenv *ve)
{
	int		i;
	int		ret[2];

	i = 0;
	ret[1] = 0;
	if (!d->cmd[1])
		return (0);
	while (d->cmd[++i])
	{
		ret[0] = export_namechecker(d->cmd[i]);
		if (ret[0] == 2)
		{
			write(2, "bash: export: `", 15);
			write(2, d->cmd[i], ft_strlen(d->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		if (ret[0] == 1)
			ret[1] = 1;
		if (ret[0])
			continue ;
		ret[0] = varenv_extract(ve, d->cmd[i]);
		if (ret[0] == -1)
			return (error_handler("export", NULL, 1));
	}
	return (ret[1]);
}
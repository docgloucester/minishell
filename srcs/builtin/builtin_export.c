/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:33:14 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/11 15:15:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_export_printargs(t_execdata *d, t_varenv *ve, char *name)
{
	char		**args;

	args = var_value_finder(ve, name, 1);
	if (!args || !args[0])
		return (1);
	print_builtin(d, "=\"");
	print_builtin(d, args[0]);
	print_builtin(d, "\"");
	free(args[0]);
	free(args);
	return (0);
}

int	builtin_export_print(t_execdata *d, t_varenv *ve)
{
	t_envitem	**list;
	int			i;

	i = 0;
	list = builtin_export_alphafinder(ve);
	if (!list)
		return (error_handler("export", NULL, 1));
	while (list[i])
	{
		print_builtin(d, "declare -x ");
		print_builtin(d, list[i]->name);
		if (list[i]->value_num)
			if (builtin_export_printargs(d, ve, list[i]->name))
				return (error_handler("export", NULL, 1));
		print_builtin(d, "\n");
		i++;
	}
	free(list);
	return (0);
}

int	builtin_export(t_execdata *d, t_varenv *ve)
{
	int		i;
	int		ret[2];

	i = 0;
	ret[1] = 0;
	if (!d->cmd[1])
		return (builtin_export_print(d, ve));
	while (d->cmd[++i])
	{
		ret[0] = push_envitem(ve, d->cmd[i]);
		if (ret[0])
		{
			if (ret[0] == -1)
				return (error_handler("export", NULL, 1));
			write(2, "bâche: export: `", 17);
			write(2, d->cmd[i], ft_strlen(d->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			ret[1] = 1;
			continue ;
		}
	}
	return (ret[1]);
}

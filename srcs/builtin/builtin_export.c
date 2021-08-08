/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:33:14 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/08 15:40:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int			builtin_export_is_asorted(t_envitem **sorted, int count)
{
	int		i;

	i = 1;
	if (count < 2)
		return (1);
	while (sorted[i])
	{
		if (ft_strncmp(sorted[i]->name, sorted[i - 1]->name, 0) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	builtin_export_alphasort(t_envitem **sorted, int count)
{
	t_envitem	*ei;
	int			i;

	ei = NULL;
	while (!builtin_export_is_asorted(sorted, count))
	{
		i = 0;
		while (i < count)
		{
			if (sorted[i + 1] && \
			ft_strncmp(sorted[i]->name, sorted[i + 1]->name, 0) > 0)
			{
				ei = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = ei;
			}
			i++;
		}
	}
}

t_envitem	**builtin_export_alphafinder(t_varenv *ve)
{
	int			i;
	t_envitem	**sorted;
	t_envitem	*ei;

	sorted = malloc(sizeof(t_envitem *) * (ve->count + 1));
	if (!sorted)
		return (NULL);
	sorted[ve->count] = NULL;
	ei = ve->envtab;
	i = 0;
	while (ei)
	{
		sorted[i] = ei;
		ei = ei->next;
		i++;
	}
	builtin_export_alphasort(sorted, ve->count);
	return (sorted);
}

int	builtin_export_print(t_varenv *ve)
{
	t_envitem	**list;
	char		**args;
	int			i;

	i = 0;
	list = builtin_export_alphafinder(ve);
	if (!list)
		return (error_handler("export", NULL, 1));
	while (list[i])
	{
		printf("declare -x %s", list[i]->name);
		if (list[i]->value_num)
		{
			args = var_value_finder(ve, list[i]->name, 1);
			if (!args || !args[0])
				return (error_handler("export", NULL, 1));
			printf("=\"%s\"", args[0]);
			free(args[0]);
			free(args);
		}
		printf("\n");
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
		return (builtin_export_print(ve));
	while (d->cmd[++i])
	{
		ret[0] = push_envitem(ve, d->cmd[i]);
		if (ret[0])
		{
			if (ret[0] == -1)
				return (error_handler("export", NULL, 1));
			write(2, "bash: export: `", 15);
			write(2, d->cmd[i], ft_strlen(d->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			ret[1] = 1;
			continue ;
		}
	}
	return (ret[1]);
}
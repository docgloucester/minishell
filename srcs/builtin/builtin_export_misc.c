/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_misc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:37:42 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/13 21:05:27 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_export_is_asorted(t_envitem **sorted, int count)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:57:47 by nouchata          #+#    #+#             */
/*   Updated: 2021/04/06 16:26:44 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "varenv.h"

void	builtin_env(t_varenv *ve)
{
	int			i;
	t_envitem	*ei;

	i = 0;
	ei = ve->envtab;
	while (ei)
	{
		printf("%s=", ei->name);
		while (i < ei->value_num)
		{
			if (i)
				printf(":");
			printf("%s", ei->value[i]);
			i++;
		}
		i = 0;
		printf("\n");
		ei = ei->next;
	}
}

void	builtin_export(t_varenv *ve, int argc, char **args)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		push_envitem(ve, args[i]);
		i++;
	}
}

void	builtin_unset(t_varenv *ve, int argc, char **args)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		pop_envitem(ve, args[i]);
		i++;
	}
}

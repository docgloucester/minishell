/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_construct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:57:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/19 11:59:02 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	varenv_extract(t_varenv *ve, char *src)
{
	t_envitem	*ei;
	t_envitem	*tem;
	int			i;

	i = 0;
	ei = malloc(sizeof(t_envitem) * 1);
	if (ei == NULL)
		return (-1);
	ei->next = NULL;
	i = find_name(ei, &src[i]);
	if (i == -1)
		return (-1);
	i = find_content(ei, &src[i + 1]);
	if (i == -1)
		return (-1);
	if (ve->envtab == NULL)
		ve->envtab = ei;
	else
	{
		tem = ve->envtab;
		while (tem->next != NULL)
			tem = tem->next;
		tem->next = ei;
	}
	return (i);
}

t_varenv	varenv_construct(char **src)
{
	t_varenv	ve;
	int			i;
	int			y;

	i = 0;
	while (src[i])
		i++;
	ve.count = i;
	ve.envtab = NULL;
	i = 0;
	while (src[i])
	{
		y = varenv_extract(&ve, src[i]);
		i++;
		if (y == -1)
		{
			varenv_kill(&ve);
			exit(EXIT_FAILURE); // A REMPLACER PAR UNE FNCT DE KILL GLOBALE
		}
	}
	return (ve);
}

void	envitem_kill(t_envitem *ei)
{
	int		i;

	i = 0;
	if (ei->name)
		free(ei->name);
	while (i < ei->value_num)
	{
		if (ei->value[i])
			free(ei->value[i]);
		i++;
	}
	if (ei->value)
		free(ei->value);
}

void	varenv_kill(t_varenv *ve)
{
	t_envitem	*old;
	t_envitem	*ei;

	kill_env_to_str(ve->env_to_str);
	ei = ve->envtab;
	while (ei)
	{
		envitem_kill(ei);
		old = ei;
		ei = ei->next;
		free(old);
	}
}

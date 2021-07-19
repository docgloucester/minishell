/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_utils_supp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:41:37 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/19 11:44:40 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	find_name(t_envitem *ei, char *src)
{
	int		i;
	int		y;
	char	*str;

	y = 0;
	i = search_char(src, '=', 1);
	if (i == -1)
		return (-1);
	if (!i)
		i = ft_strlen(src);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (-1);
	while (y < i)
	{
		str[y] = src[y];
		y++;
	}
	str[y] = 0;
	ei->name = str;
	return (i);
}

int	find_content(t_envitem *ei, char *src)
{
	int		i;
	int		y;
	char	**strs;

	i = 0;
	y = count_varenv_occ(src);
	ei->value_num = y;
	strs = malloc(sizeof(char *) * (y + 1));
	if (!strs)
		return (-1);
	strs[y] = NULL;
	y = 0;
	while (y < ei->value_num)
	{
		i = i + 1 + extract_content(&strs[y], &src[i]);
		if (!&strs[y])
			return (-1);
		y++;
	}
	ei->value = strs;
	return (0);
}

void	pop_envitem_supp(t_varenv *ve, t_envitem *ei, t_envitem *tmp)
{
	envitem_kill(ei);
	if (tmp)
	{
		tmp->next = ei->next;
		free(ei);
	}
	else
	{
		ve->envtab = ei->next;
		free(ei);
	}
}

int	pop_envitem(t_varenv *ve, char *str, int length_compare)
{
	t_envitem	*ei;
	t_envitem	*tmp;

	ei = ve->envtab;
	tmp = NULL;
	while (ei)
	{
		if (!ft_strncmp(str, ei->name, length_compare))
		{
			pop_envitem_supp(ve, ei, tmp);
			ve->count--;
			return (1);
		}
		tmp = ei;
		ei = ei->next;
	}
	return (0);
}

int	push_envitem(t_varenv *ve, char *src)
{
	int		i;
	int		y;

	y = search_char(src, '=', 1);
	if (!ft_strlen(src) || src[0] == '=' || src[0] == ' ' || \
	(search_char(src, ' ', 0) && y > search_char(src, ' ', 1)))
		return (1);
	if (!y)
		return (blank_var(ve, src));
	pop_envitem(ve, src, y);
	i = varenv_extract(ve, src); // ne gère pas les variables sans valeurs
	ve->count++;
	return (i);
}

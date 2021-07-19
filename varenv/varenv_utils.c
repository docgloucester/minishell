/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:42:51 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/19 11:55:14 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	search_char(char *str, char c, int returnlength)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (returnlength && str[i] == c)
		return (i);
	if (!returnlength && str[i] == c)
		return (1);
	return (0);
}

int	count_varenv_occ(char *src)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (src[i])
	{
		if (src[i] == ':')
			y++;
		i++;
	}
	return (y + 1);
}

int	extract_content(char **str, char *src)
{
	int		y;
	int		i;
	char	*res;

	i = 0;
	y = search_char(src, ':', 1);
	if (src[y] != ':' && (y == 0 || y == -1))
		y = search_char(src, 0, 1);
	if (y == -1)
	{
		*str = NULL;
		return (0);
	}
	res = malloc(sizeof(char) * y + 1);
	while (i < y)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = 0;
	*str = res;
	return (y);
}

int	blank_var(t_varenv *ve, char *src)
{
	t_envitem	*ei;
	t_envitem	*last;

	ei = ve->envtab;
	last = NULL;
	while (ei)
	{
		if (!ft_strncmp(src, ei->name, 0))
			return (0);
		if (!ei->next)
			last = ei;
		ei = ei->next;
	}
	ei = malloc(sizeof(t_envitem) * 1);
	if (!ei)
		return (-1);
	ei->next = NULL;
	ei->value_num = 0;
	ei->value = NULL;
	if (find_name(ei, src) == -1)
		return (-1);
	last->next = ei;
	ve->count++;
	return (0);
}
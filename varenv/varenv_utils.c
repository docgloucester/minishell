/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:42:51 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 22:55:16 by nouchata         ###   ########.fr       */
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

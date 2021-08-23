/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:16:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/23 15:18:16 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

long	find_char_not_escaped(char *src, char c, int already_find)
{
	long	i;
	long	y;

	i = -1;
	y = 0;
	while (src[++i])
		if (src[i] == c)
		{
			if (i && src[i - 1] == '\\')
				continue ;
			if (already_find && y < already_find)
			{
				if (y < already_find)
					y++;
				else
					return (i);
			}
			else
				return (i);
		}
	return (-1);
}

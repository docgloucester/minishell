/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkseg_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:54:28 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/23 17:50:17 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

int		count_all_sep(char *src)
{
	int		i;
	int		sep;
	char	last;

	i = 0;
	sep = 0;
	last = 0;
	while (src[i])
	{
		i = find_next_sep(&src[0]);
		if (i == -1)
			break ;
		if (last != ' ' && i)
			sep++;
		last = src[i];
		src = &src[i + 1];
		src = to_next_char(src, ' ');
	}
	return (sep);
}

int		find_next_sep(char *src)
{
	int		distance[2];

	distance[0] = -1;
	distance[1] = -1;
	distance[0] = find_char_not_escaped(src, ' ', 0);
	if (distance[0] == -1)
		distance[0] = 2147483647;
 	distance[1] = find_char_not_escaped(src, '<', 0);
	if (distance[1] != -1 && distance[1] < distance[0])
		distance[0] = distance[1];
	distance[1] = find_char_not_escaped(src, '>', 0);
	if (distance[1] != -1 && distance[1] < distance[0])
		distance[0] = distance[1];
	if (distance[0] == 2147483647)
		return (-1);
	return (distance[0]);
}
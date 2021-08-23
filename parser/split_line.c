/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:33 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/23 16:08:35 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include "parser.h"

t_cmdchunk	*split_line_semicol(char *line)
{
	unsigned int	semicol_counter;
	t_cmdchunk		*ret;
	unsigned int	i;
	long			a[2];

	semicol_counter = 0;
	while (find_char_not_escaped(line, ';', semicol_counter) != -1)
		semicol_counter++;
	i = -1;
	a[0] = 0;
	ret = NULL;
	while (++i < semicol_counter)
	{
		a[1] = find_char_not_escaped(&line[a[0]], ';', 0);
		if (!(chunkadd(&ret, newchunk(ft_substr(line, a[0] , a[1]), SEMICO))))
			return (NULL);
		a[0] += a[1] + 1;
	}
	a[1] = find_char_not_escaped(line, ';', semicol_counter - 1);
	if (!(chunkadd(&ret,
		newchunk(ft_substr(line, a[1] + 1, ft_strlen(line) - a[1]), SEMICO))))
		return (NULL);
	return ret;
}

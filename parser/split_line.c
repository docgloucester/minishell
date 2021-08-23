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

t_cmdchunk	*split_line(char *line)
{
	unsigned int	semicol_counter;
	t_cmdchunk		*ret;
	unsigned int	i;
	long			a;

	semicol_counter = 0;
	while (find_char_not_escaped(line, ';', semicol_counter) != -1)
		semicol_counter++;
	i = -1;
	a = 0;
	while (++i < semicol_counter)
	{
		if (!(chunkadd(&ret, newchunk(ft_substr(line, a, find_char_not_escaped(&line[a], ';', 0)), SEMICO))))
			return (NULL);
		a = find_char_not_escaped(&line[a], ';', 0) + 1;
	}
	if (!(chunkadd(&ret, newchunk(ft_substr(line, a, ft_strlen(line)), SEMICO))))
			return (NULL);
	return ret;
}

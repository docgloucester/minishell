/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:33 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/24 14:22:27 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_valid_separator(char *str, int i)
{
	unsigned int	dbqcount;
	unsigned int	qcount;
	int				pos;

	pos = -1;
	dbqcount = 0;
	qcount = 0;
	while (++pos < i)
	{
		if (str[pos] == '\'')
			qcount++;
		if (str[pos] == '\"')
			dbqcount++;
	}
	if ((str[i] == '|' || str[i] == ';')
		&& str[i - 1] != '\\'
		&& qcount % 2 == 0 && dbqcount % 2 == 0)
		return (1);
	return (0);
}

int	sep_detector(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_valid_separator(str, i))
		i++;
	return (i + 1);
}

t_cmdchunk *chunk_list_creator(char *str)
{
	int		i;
	int		y;
	t_cmdchunk *list;
	char *cstr;

	i = 0;
	y = 0;
	list = NULL;
	while (i < (int)ft_strlen(str))
	{
		cstr = &str[i];
		i += to_next_char(&cstr, ' ', 0);
		if (!str[i])
			break ;
		y = sep_detector(&str[i]);
		chunkadd(&list, newchunk(ft_substr(str, i, y - 1), str[i + y - 1]));
		i += y;
	}
	return (list);
}
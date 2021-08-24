/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:16:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 18:01:02 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

int		count_strs(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int		find_size_of_current_block(char *src)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = 0;
	if (!ft_strncmp(&src[i], "<<", 2) || !ft_strncmp(&src[i], ">>", 2))
		return (2);
	if (src[i] == '<' || src[i] == '>')
		return (1);
	while (src[i])
	{
		if (src[i] == '\\')
			i += 2;
		if (src[i] && !quotes && (src[i] == '\'' || src[i] == '\"'))
			quotes = src[i];
		else if (src[i] && quotes && src[i] == quotes)
			quotes = 0;
		if (src[i] && !quotes && (src[i] == '<' || src[i] == '>' || \
		src[i] == ' '))
			break ;
		if (src[i])
			i++;
	}
	return (i);
}

int		count_all_segments(char *src)
{
	int		i;
	int		seg;
	char	*tnc;

	i = 0;
	seg = 0;
	tnc = &src[i];
	i += to_next_char(&tnc, ' ', 0);
	while (src[i])
	{
		tnc = &src[i];
		i += to_next_char(&tnc, ' ', 0);
		if (!src[i])
			break;
		i += find_size_of_current_block(&src[i]);
		seg++;
	}
	return (seg);
}

long	fchar_nesc(char *src, char c, int already_find)
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
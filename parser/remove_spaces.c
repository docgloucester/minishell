/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:14:29 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/23 17:09:39 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

/* type : 0=all / 1=from_start / 2=from_end */
int		count_spaces(char *src, int type)
{
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	if (type == 0)
	{
		while (src[++i[0]])
			if (src[i[0]] == ' ')
				i[1]++;
		return (i[1]);
	}
	if (type == 1)
	{
		while (src[++i[0]] && src[i[0]] == ' ')
			i[1]++;
		return (i[1]);
	}
	if (type == 2)
	{
		i[0] = ft_strlen(src);
		while (--i[0] >= 0 && src[i[0]] == ' ')
			i[1]++;
		return (i[1]);
	}
	return (-1);
}

/* type : 0=all / 1=surrond_spaces */
int		wout_spaces_filler(char *new, char *src, int type)
{
	int		i[3];
	
	i[0] = 0;
	i[1] = 0;
	i[2] = ft_strlen(src) - count_spaces(src, 2);
	while (src && src[i[0]] == ' ')
			i[0]++;
	while (src && i[0] < i[2])
	{
		if (!type && src[i[0]] != ' ')
		{
			new[i[1]] = src[i[0]];
			i[1]++;
		}
		if (type)
		{
			new[i[1]] = src[i[0]];
			i[1]++;
		}
		i[0]++;
	}
	return (0);
}

int		check_if_full_spaces(char *src)
{
	int		i;

	i = 0;
	while (src && src[i])
	{
		if (src[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*to_next_char(char *src, char c)
{
	int		i;

	i = 0;
	while (src && src[i] && src[i] == c)
		i++;
	return (&src[i]);
}

int		remove_spaces(char **src, int just_surround_spaces)
{
	char	*new;
	int		spaces;

	spaces = 0;
	if (just_surround_spaces)
		just_surround_spaces = check_if_full_spaces(*src);
	if (just_surround_spaces)
	{
		spaces += count_spaces(*src, 1);
		spaces += count_spaces(*src, 2);
	}
	else
		spaces += count_spaces(*src, 0);
	new = malloc(sizeof(char) * (ft_strlen(*src) - spaces + 1));
	if (!new)
		return (-1);
	new[ft_strlen(*src) - spaces] = 0;
	wout_spaces_filler(new, *src, just_surround_spaces);
	printf("{%s}\n", new);
	free(new);
	// free(*src);
	// *src = new;
	return (0);
}
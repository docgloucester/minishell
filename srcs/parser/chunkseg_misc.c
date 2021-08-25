/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkseg_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:54:28 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/25 16:30:48 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

char	**kill_segments(char **segs, int count)
{
	int		i;

	i = 0;
	while (segs && count && i < count)
	{
		free(segs[i]);
		i++;
	}
	while (segs && !count && segs[i])
	{
		free(segs[i]);
		i++;		
	}
	if (segs)
		free(segs);
	return (NULL);
}

char	*extract_chunkseg_data(char *src, int length)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	res[length] = 0;
	while (i < length)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}

char	**extract_segments(char *src)
{
	char	**segs;
	int		segs_num;
	int		i[2];

	segs_num = count_all_segments(src);
	i[1] = 0;
	i[0] = 0;
	segs = malloc(sizeof(char *) * (segs_num + 1));
	if (!segs)
		return (NULL);
	ft_memset(segs, 0, sizeof(char *) * (segs_num + 1));
	while (i[1] < segs_num)
	{
		src = &src[to_next_char(&src, ' ', 0)];
		i[0] = find_size_of_current_block(src);
		segs[i[1]] = extract_chunkseg_data(src, i[0]);
		if (!segs[i[1]])
			return (kill_segments(segs, 0));
		src = &src[i[0]];
		i[1]++;
	}
	return (segs);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkseg_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:54:28 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 14:09:20 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

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
	if (remove_spaces(&res, 1) == -1)
	{
		free(res);
		return (NULL);
	}
	return (res);
}


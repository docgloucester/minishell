/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 10:47:19 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/08 13:52:34 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s1_end;

	i = 0;
	if (dest)
		while (dest[i] && i < size)
			i++;
	s1_end = i;
	while (src[i - s1_end] && i < size - 1 && size)
	{
		dest[i] = src[i - s1_end];
		i++;
	}
	if (s1_end < size)
		if (dest)
			dest[i] = '\0';
	return (s1_end + ft_strlen(src));
}

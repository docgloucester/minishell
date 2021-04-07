/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 10:47:19 by nouchata          #+#    #+#             */
/*   Updated: 2019/11/11 13:02:54 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s1_end;

	i = 0;
	while (dest ? dest[i] && i < size : 0)
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

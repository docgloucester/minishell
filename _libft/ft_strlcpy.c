/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:54:00 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/08 13:47:15 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (i < dstsize - 1 && dstsize > 0 && src[i] && dst)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		if (dst)
			dst[i] = 0;
	i = 0;
	while (src[i])
		i++;
	return (i);
}

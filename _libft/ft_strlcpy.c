/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:54:00 by nouchata          #+#    #+#             */
/*   Updated: 2019/11/09 18:45:19 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && dstsize > 0 && (src ? src[i] : 0) && dst)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		if (dst)
			dst[i] = 0;
	i = 0;
	while (src ? src[i] : 0)
		i++;
	return (i);
}

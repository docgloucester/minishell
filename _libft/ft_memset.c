/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:39:11 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/09 14:42:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	while (i < n)
	{
		tmp[i] = (char)c;
		i++;
	}
	return (s);
}

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	unsigned int	i;
// 	unsigned char	*dest;

// 	i = 0;
// 	dest = (unsigned char *)b;
// 	while (i < len)
// 	{
// 		dest[i] = (unsigned char)c;
// 		i++;
// 	}
// 	b = (void *)dest;
// 	return (b);
// }

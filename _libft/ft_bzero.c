/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:46:15 by nouchata          #+#    #+#             */
/*   Updated: 2019/11/09 18:21:09 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	dest = (unsigned char *)s;
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			dest[i] = 0;
			i++;
		}
	}
}

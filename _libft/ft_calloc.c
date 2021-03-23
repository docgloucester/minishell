/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:26:03 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 11:48:16 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*res;
	unsigned char	*fill;
	unsigned int	i;

	i = 0;
	res = NULL;
	if (size == 0)
		return (malloc(0));
	res = malloc(count * size);
	if (!res)
		return (NULL);
	fill = (unsigned char *)res;
	while (i < count * size)
	{
		fill[i] = 0;
		i++;
	}
	return (res);
}

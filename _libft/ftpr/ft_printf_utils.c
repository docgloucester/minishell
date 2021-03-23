/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:01:56 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 13:31:31 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

unsigned int	pr_strlen(const char *src)
{
	unsigned int	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		i++;
	return (i);
}

void	pr_mirrorswap(char *src)
{
	unsigned int	i;
	char			c;
	unsigned int	size;

	i = 0;
	size = pr_strlen(src);
	while (i < size / 2)
	{
		c = src[i];
		src[i] = src[size - 1 - i];
		src[size - 1 - i] = c;
		i++;
	}
}

unsigned int	pr_printchar(const char *src, int len)
{
	if (!src)
		return (0);
	if (len == -1)
		len = pr_strlen(src);
	write(1, src, len);
	return (len);
}

char	*pr_calloc(size_t size, char filling)
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	while (i < size)
		res[i++] = filling;
	res[i] = 0;
	return (res);
}

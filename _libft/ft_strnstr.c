/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:16:50 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 11:18:38 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr_supp(const char *haystack, const char *needle, size_t len, \
unsigned int *i)
{
	unsigned int	y;

	y = *i;
	while (haystack[y] == needle[y - *i])
	{
		if (needle[y - *i + 1] == 0 && y <= len)
			return (1);
		if (needle[y - *i + 1] == 0 && !(y <= len))
			return (0);
		y++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	y;
	char			*cpy;

	i = 0;
	y = 0;
	cpy = (char *)haystack;
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[y])
		{
			if (ft_strnstr_supp(haystack, needle, len, &i))
				return (&cpy[i]);
			else
				return (NULL);
		}
		y = 0;
		i++;
	}
	if (needle[0])
		return (NULL);
	return (cpy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:14:54 by nouchata          #+#    #+#             */
/*   Updated: 2019/11/09 18:22:10 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*cpy;

	i = 0;
	cpy = (char *)s;
	if (c == 0)
	{
		while (s[i])
			i++;
		return (&cpy[i]);
	}
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&cpy[i]);
		i++;
	}
	return (NULL);
}

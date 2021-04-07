/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:16:00 by nouchata          #+#    #+#             */
/*   Updated: 2019/11/09 18:34:13 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	long			str_len;
	char			*cpy;

	i = 0;
	str_len = ft_strlen(s);
	cpy = (char *)s;
	if (c == 0)
		return (&cpy[str_len]);
	str_len--;
	while (str_len >= 0)
	{
		if (s[str_len] == (char)c)
			return (&cpy[str_len]);
		str_len--;
	}
	return (NULL);
}

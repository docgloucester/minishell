/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:16:32 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/26 20:00:13 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		j;

	j = 0;
	r = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1 && *s1)
	{
		r[j] = *s1;
		s1++;
		j++;
	}
	while (s2 && *s2)
	{
		r[j] = *s2;
		s2++;
		j++;
	}
	r[j] = '\0';
	return (r);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:12:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:20:43 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	str_size;
	unsigned int	i;
	char			*dup;

	i = 0;
	str_size = ft_strlen(s1);
	if (!str_size)
		return (malloc(0));
	dup = malloc((str_size + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < str_size)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

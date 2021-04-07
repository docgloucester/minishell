/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:13:07 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 11:36:56 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;
	unsigned int	part_size;

	i = -1;
	part_size = 0;
	if (s && ft_strlen(s) > start)
		part_size = ft_strlen(&s[start]);
	if (!part_size)
		return (ft_calloc(1, 1));
	if (part_size <= len)
		subs = malloc((part_size + 1) * sizeof(char));
	else
		subs = malloc((len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	while (++i < len && s[start + i])
		subs[i] = s[start + i];
	subs[i] = 0;
	return (subs);
}

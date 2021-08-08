/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:16:32 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 11:21:16 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_supp(const char **s1, const char **s2, char **res)
{
	int	i;
	int	y;

	i = -1;
	while (*s1[++i])
		*res[i] = *s1[i];
	y = i;
	i = -1;
	while (*s2[++i])
	{
		*res[y] = *s2[i];
		y++;
	}
	*res[y] = 0;
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	char			*res;
	long			all;

	all = -1;
	if (s1 && s2)
		all = ft_strlen(s1) + ft_strlen(s2);
	if (all == -1)
	{
		res = malloc(0);
		if (res)
			return (res);
		return (NULL);
	}
	res = malloc((all + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strjoin_supp(&s1, &s2, &res);
	return (res);
}

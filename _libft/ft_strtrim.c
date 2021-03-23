/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:32:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:00:32 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlentrim_supp(unsigned int *count, char *is_trim, \
unsigned int *y, int rev)
{
	*count = *count + 1;
	*is_trim = 0;
	*y = 0;
	if (rev)
		return (-1);
	return (1);
}

static size_t	ft_strlentrim(char const *s1, char const *s2, int rev)
{
	long			i;
	unsigned int	y;
	unsigned int	count;
	char			is_trim;

	y = 0;
	i = 0;
	if (rev)
		i = ft_strlen(s1) - 1;
	count = 0;
	if (!s1)
		return (0);
	while ((rev && i >= 0) || (!rev && s1[i]))
	{
		while (s2 && s2[y])
		{
			if (s1[i] == s2[y])
				is_trim = 1;
			y++;
		}
		if (!is_trim)
			break ;
		i += ft_strlentrim_supp(&count, &is_trim, &y, rev);
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;
	unsigned int	length;
	char			*res;

	start = ft_strlentrim(s1, s2, 0);
	end = ft_strlentrim(s1, s2, 1);
	length = ft_strlen(s1);
	i = 0;
	if ((length - start - end) == 0)
		return (ft_calloc(1, 1));
	res = malloc((length - start - end + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (start < length - end)
	{
		res[i] = s1[start];
		start++;
		i++;
	}
	res[i] = 0;
	return (res);
}

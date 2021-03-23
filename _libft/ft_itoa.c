/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:29:24 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:40:48 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counter(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	ft_reverser(char *str)
{
	unsigned int	i;
	unsigned int	length;
	char			tmp;

	i = 0;
	length = ft_strlen(str);
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

void	ft_intmin(char **res)
{
	char			*intmin;
	int				i;

	intmin = "-2147483648";
	i = 0;
	*res = malloc(sizeof(char) * 12);
	if (!*res)
		*res = NULL;
	while (*res && i < 11)
	{
		*res[i] = intmin[i];
		i++;
	}
	if (*res)
		*res[i] = 0;
}

char	*ft_exceptions(int n)
{
	char			*res;

	if (n == 0)
	{
		res = malloc(sizeof(char) * 2);
		if (!res)
			return (NULL);
		res[0] = '0';
		res[1] = 0;
	}
	if (n == -2147483648)
		ft_intmin(&res);
	return (res);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*res;
	int				neg;

	i = 0;
	if (n == -2147483648 || n == 0)
		return (ft_exceptions(n));
	res = malloc(sizeof(char) * (ft_counter(n) + 1));
	if (!res)
		return (NULL);
	neg = n < 0;
	if (neg)
		n = -n;
	while (n)
	{
		res[i++] = n % 10 + 48;
		n = n / 10;
	}
	if (neg)
		res[i++] = '-';
	res[i] = 0;
	ft_reverser(res);
	return (res);
}

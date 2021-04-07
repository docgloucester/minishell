/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_relatives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:03:34 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 14:01:43 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

unsigned int	pr_num_len(long int num)
{
	unsigned int	i;

	i = 0;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*pr_itoa_supp(long *num, long *src, unsigned int *size, \
unsigned int *i)
{
	if (!*src)
		return (NULL);
	*size = 0;
	*num = *src;
	if (*num < 0)
	{
		*num *= -1;
		*size = 1;
	}
	*size = *size + pr_num_len(*src);
	*i = 0;
	return (pr_calloc(sizeof(char) * *size, ' '));
}

char	*pr_itoa(long int src)
{
	char			*res;
	unsigned int	size;
	unsigned int	i;
	long int		num;

	res = pr_itoa_supp(&num, &src, &size, &i);
	if (!src)
		return (pr_calloc(sizeof(char) * 1, '0'));
	if (!res)
		return (NULL);
	while (res[i])
	{
		if (num)
		{
			res[i++] = num % 10 + 48;
			num = num / 10;
		}
		else
			res[i++] = '-';
	}
	pr_mirrorswap(res);
	return (res);
}

char	*pr_make_int(int num, t_flags f)
{
	char			*res;

	res = pr_itoa((long int)num);
	if (!res)
		return (NULL);
	if (res[0] == '-')
	{
		res = pr_neg_prec_handler(res, f);
		if (!res)
			return (NULL);
	}
	else
	{
		res = pr_num_prec_handler(res, f);
		if (!res)
			return (NULL);
	}
	res = pr_field_handler(res, f);
	if (!res)
		return (NULL);
	if (!f.is_prec && !f.l_align && f.z_fill)
		pr_zero_handler(res);
	return (res);
}

char	*pr_make_uint(unsigned int num, t_flags f)
{
	char			*res;

	res = pr_itoa((long int)num);
	if (!res)
		return (NULL);
	res = pr_num_prec_handler(res, f);
	if (!res)
		return (NULL);
	res = pr_field_handler(res, f);
	if (!res)
		return (NULL);
	if (!f.is_prec && !f.l_align && f.z_fill)
		pr_zero_handler(res);
	return (res);
}

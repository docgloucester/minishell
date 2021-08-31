/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_relatives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:34:53 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 14:14:51 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

unsigned int	pr_ptr_len(long ptr)
{
	unsigned int	i;

	i = 0;
	while (ptr)
	{
		ptr = ptr / 16;
		i++;
	}
	return (i);
}

char	*pr_make_hexnum(long dec, char alphabet)
{
	char			*res;
	unsigned int	size;
	unsigned int	i;

	size = pr_ptr_len(dec);
	i = 0;
	if (!dec)
		return (pr_calloc(sizeof(char) * 1, '0'));
	res = pr_calloc(sizeof(char) * size, ' ');
	if (!res)
		return (NULL);
	while (i < size)
	{
		if (dec % 16 > 9)
			res[i++] = dec % 16 + alphabet - 10;
		else
			res[i++] = dec % 16 + 48;
		dec /= 16;
	}
	i = 0;
	pr_mirrorswap(res);
	return (res);
}

char	*pr_make_xint(unsigned int dec, t_flags f, int maj)
{
	char			*res;

	if (maj)
		res = pr_make_hexnum(dec, 'A');
	else
		res = pr_make_hexnum(dec, 'a');
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

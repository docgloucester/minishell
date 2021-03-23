/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_relatives.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:06:36 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 13:36:06 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

char	*pr_make_char(char c, t_flags f)
{
	char			*str;

	if (f.f_size > 1)
		str = pr_calloc(sizeof(char) * f.f_size, ' ');
	else
		str = pr_calloc(sizeof(char) * 1, ' ');
	if (f.f_size > 1 && !f.l_align)
		str[f.f_size - 1] = c;
	else
		str[0] = c;
	if (c == '%' && !f.l_align && f.z_fill)
		pr_zero_handler(str);
	return (str);
}

char	*pr_make_str(char *str, t_flags f)
{
	char			*res;
	unsigned int	size;

	if (!str)
		str = "(null)";
	size = pr_strlen(str);
	if (f.is_prec && f.prec < size)
		size = f.prec;
	res = pr_calloc(sizeof(char) * size, ' ');
	if (!res)
		return (NULL);
	size = 0;
	while (res[size])
	{
		res[size] = str[size];
		size++;
	}
	res = pr_field_handler(res, f);
	if (!res)
		return (NULL);
	return (res);
}

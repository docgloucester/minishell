/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_relatives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:58:03 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:50:04 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

int	pr_conversion_spec(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.' && str[i] != '*' && str[i] != '-' && !(str[i] >= '0' \
		 && str[i] <= '9'))
			break ;
		i++;
	}
	if (!str[i])
		return (-1);
	return (i + 1);
}

char	*pr_make_arg(char c, t_flags f, va_list ap)
{
	char		*res;

	res = NULL;
	if (c == 'c')
		res = pr_make_char(va_arg(ap, int), f);
	else if (c == '%')
		res = pr_make_char('%', f);
	else if (c == 's')
		res = pr_make_str(va_arg(ap, char *), f);
	else if (c == 'd' || c == 'i')
		res = pr_make_int(va_arg(ap, int), f);
	else if (c == 'u')
		res = pr_make_uint(va_arg(ap, unsigned int), f);
	else if (c == 'x' || c == 'X')
		res = pr_make_xint(va_arg(ap, unsigned int), f, c == 'X');
	else if (c == 'p')
		res = pr_make_ptr(va_arg(ap, void *), f);
	return (res);
}

int	pr_parsing(const char *str, va_list ap, int *p_char)
{
	int			it;
	t_flags		f;
	char		*res;

	it = pr_conversion_spec(&str[1]);
	if (it == -1)
		return (*p_char = -1);
	if (str[it] != 'c' && str[it] != 's' && str[it] != 'p' && str[it] != \
	 'i' && str[it] != 'd' && str[it] != 'u' && str[it] != 'x' && str[it] != \
	  'X' && str[it] != '%')
	{
		*p_char += pr_printchar(str, 1);
		return (1);
	}
	f = pr_get_flags(&str[1], ap);
	res = pr_make_arg(str[it], f, ap);
	if (!res)
		return (*p_char = -1);
	if (str[it] == 'c' && res[0] == 0 && !f.f_size)
		f.f_size = 1;
	if (str[it] == 'c' && f.f_size)
		*p_char += pr_printchar(res, f.f_size);
	else
		*p_char += pr_printchar(res, -1);
	free(res);
	return (it);
}

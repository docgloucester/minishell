/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_relatives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:51:54 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:52:49 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

char	*pr_make_ptr(void *ptr, t_flags f)
{
	unsigned int	i;
	unsigned int	size;
	char			*res;
	char			*hex;

	i = 2;
	if (!ptr)
		return (pr_null_pointer(f));
	size = pr_ptr_len((long int)ptr) + 2;
	res = pr_calloc(sizeof(char) * size, ' ');
	if (!res)
		return (NULL);
	hex = pr_make_hexnum((long int)ptr, 'a');
	if (!hex)
		return (NULL);
	res[0] = '0';
	res[1] = 'x';
	while (i < size)
	{
		res[i] = hex[i - 2];
		i++;
	}
	res = pr_field_handler(res, f);
	free(hex);
	return (res);
}

char	*pr_null_pointer(t_flags f)
{
	char			*res;

	res = pr_calloc(sizeof(char) * 3, ' ');
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = 'x';
	res[2] = '0';
	res = pr_field_handler(res, f);
	return (res);
}

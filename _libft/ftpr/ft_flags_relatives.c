/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_relatives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:37:59 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 14:18:45 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

char	*pr_field_handler(char *src, t_flags f)
{
	char			*res;
	int				is_size_bigger;
	int				pos;
	int				i;

	is_size_bigger = f.f_size > pr_strlen(src);
	if (!is_size_bigger)
		return (src);
	pos = 0;
	if (!(f.l_align || !is_size_bigger))
		pos = f.f_size - pr_strlen(src);
	i = 0;
	res = pr_calloc(sizeof(char) * f.f_size, ' ');
	if (!res)
		return (NULL);
	while (src[i])
		res[pos++] = src[i++];
	free(src);
	return (res);
}

void	pr_zero_handler(char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '-')
		{
			src[i] = ' ';
			src[0] = '-';
			break ;
		}
		i++;
	}
	i = 0;
	if (src[0] == '-')
		i = 1;
	while (src[i] == ' ')
	{
		src[i] = '0';
		i++;
	}
}

char	*pr_num_prec_handler(char *src, t_flags f)
{
	char			*res;
	unsigned int	size;
	unsigned int	i;

	size = pr_strlen(src);
	i = 0;
	if (!f.prec && f.is_prec && src[0] == '0' && size == 1)
		src[0] = 0;
	if ((int)(f.prec - size) > 0)
	{
		res = pr_calloc(sizeof(char) * f.prec, ' ');
		if (!res)
			return (NULL);
		while (i < f.prec - size)
			res[i++] = '0';
		i = 0;
		while (res[i + f.prec - size])
		{
			res[i + f.prec - size] = src[i];
			i++;
		}
		free(src);
		return (res);
	}
	return (src);
}

char	*pr_neg_prec_handler(char *src, t_flags f)
{
	char			*res;
	unsigned int	size;
	unsigned int	i;

	size = pr_strlen(src) - 1;
	i = 1;
	if ((int)(f.prec - size) > 0)
	{
		res = pr_calloc(sizeof(char) * (f.prec + 1), '-');
		if (!res)
			return (NULL);
		while (i < f.prec - size + 1)
			res[i++] = '0';
		i = 1;
		while (res[i + f.prec - size])
		{
			res[i + f.prec - size] = src[i];
			i++;
		}
		free(src);
		return (res);
	}
	return (src);
}

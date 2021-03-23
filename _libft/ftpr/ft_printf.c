/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:37:26 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 13:31:55 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

int	ft_printf(const char *stnce, ...)
{
	int				p_char;
	int				i;
	va_list			ap;

	p_char = 0;
	i = 0;
	if (!stnce)
		return (-1);
	va_start(ap, stnce);
	while (stnce[i] && p_char != -1)
	{
		if (stnce[i] != '%')
		{
			p_char += pr_printchar(&stnce[i], 1);
			i++;
		}
		else
		{
			i = i + 1 + pr_parsing(&stnce[i], ap, &p_char);
		}
	}
	va_end(ap);
	return (p_char);
}

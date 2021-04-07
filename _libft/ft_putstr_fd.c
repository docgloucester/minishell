/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:00:40 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 10:47:06 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;
	unsigned int	length;

	i = 0;
	length = 0;
	if (s)
		length = ft_strlen(s);
	while (i < length && fd)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

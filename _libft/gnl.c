/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:08:46 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 11:02:56 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	gnl_assign(int *is_nl, char **res, int *rres, long *pos)
{
	*is_nl = 0;
	*res = 0;
	*rres = -1;
	if (*pos)
		*rres = 1;
}

void	gnl_assign_supp(int *rres, long *pos, int *is_nl)
{
	if (*is_nl == 2 && *rres != -1)
		*rres = 0;
	if (*is_nl == 2)
		*pos = 0;
}

int	get_next_line(int fd, char **line)
{
	static char		buff[BUFFER_SIZE];
	char			*res;
	int				rres;
	static long		pos = 0;
	int				is_nl;

	gnl_assign(&is_nl, &res, &rres, &pos);
	if (!line)
		return (-1);
	while (!is_nl && BUFFER_SIZE != 0)
	{
		if (pos == 0)
			rres = read(fd, buff, BUFFER_SIZE);
		res = ft_link(res, ft_stck(buff, &pos, &is_nl));
		if (!res)
			return (-1);
		ft_reset(buff, &pos, &is_nl, fd);
	}
	gnl_assign_supp(&rres, &pos, &is_nl);
	*line = res;
	if (rres > 0)
		return (1);
	return (rres);
}

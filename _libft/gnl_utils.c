/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:04:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:19:31 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

long	gnl_strlen(char *str)
{
	long	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_reset(char *buff, long *pos, int *is_nl, int fd)
{
	unsigned int	i;

	i = 0;
	if (*is_nl == 1 && !fd && *pos < BUFFER_SIZE - 1 && !buff[*pos + 1])
		*is_nl = 3;
	while (i < BUFFER_SIZE && ((*is_nl == 1 && *pos == BUFFER_SIZE - 1) \
	 || (*is_nl != 1)))
	{
		if (!buff[i])
			break ;
		buff[i] = 0;
		i++;
	}
	if (((*is_nl == 1 && *pos == BUFFER_SIZE - 1) || (*is_nl != 1)))
		*pos = 0;
	else
		*pos = *pos + 1;
	if (*is_nl == 3)
		*is_nl = 1;
}

char	*ft_stck(char *buff, long *pos, int *is_nl)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!res)
		return (0);
	while (*pos < BUFFER_SIZE)
	{
		if (buff[*pos] == '\n')
			*is_nl = 1;
		if (buff[*pos] == 0)
			*is_nl = 2;
		if (*is_nl)
			break ;
		res[i] = buff[*pos];
		*pos = *pos + 1;
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_link(char *s1, char *s2)
{
	char			*res;
	long			s1_len;
	long			s2_len;
	unsigned int	i;

	i = -1;
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	if (!s2)
		s2_len = -1;
	if (s2_len == -1)
		return (0);
	res = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (0);
	while (++i < s1_len)
		res[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		res[s1_len + i] = s2[i];
	res[s1_len + i] = 0;
	free(s1);
	free(s2);
	return (res);
}

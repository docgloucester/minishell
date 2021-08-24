/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:33 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/24 14:22:27 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include "parser.h"

t_cmdchunk	*split_line(char *line, char sep, int septype)
{
	unsigned int	semicol_counter;
	t_cmdchunk		*ret;
	unsigned int	i;
	long			a[2];

	semicol_counter = 0;
	while (fchar_nesc(line, sep, semicol_counter) != -1)
		semicol_counter++;
	i = -1;
	a[0] = 0;
	ret = NULL;
	while (++i < semicol_counter)
	{
		a[1] = fchar_nesc(&line[a[0]], sep, 0);
		if (!(chunkadd(&ret, newchunk(ft_substr(line, a[0] , a[1]), septype))))
			return (NULL);
		a[0] += a[1] + 1;
	}
	a[1] = fchar_nesc(line, sep, semicol_counter - 1);
	if (!(chunkadd(&ret,
		newchunk(ft_substr(line, a[1] + 1, ft_strlen(line) - a[1]), septype))))
		return (NULL);
	return (ret);
}

t_cmdchunk	*perform_split(char *line)
{
	t_cmdchunk	*split;
	t_cmdchunk	*curr;
	t_cmdchunk	*pipe_split;

	split = split_line(line, ';', SEMICO);
	curr = split;
	while (curr)
	{
		pipe_split = split_line(curr->cmd, '|', PIPE);
		replace_node_by_list(&curr, &pipe_split);
		while (curr && curr->sep_type == PIPE)
			curr = curr->next;
	}
	return (split);
}

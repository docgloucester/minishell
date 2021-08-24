/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:33 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/23 16:08:35 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include "parser.h"

/*int	split_subline_pipe(t_cmdchunk **split)
{
	unsigned int	pipe_counter;
	t_cmdchunk		*to_insert;
	unsigned int	i;
	long			a[2];

	while (*split)
	{
printf("splitting \"%s\"...\n", (*split)->cmd);
		pipe_counter = 0;
		while (find_char_not_escaped((*split)->cmd, '|', pipe_counter) != -1)
			pipe_counter++;
		i = -1;
		a[0] = 0;
		to_insert = NULL;
		while (++i < pipe_counter)
		{
			a[1] = find_char_not_escaped(&(*split)->cmd[a[0]], '|', 0);
			if (!(chunkadd(&to_insert, newchunk(ft_substr((*split)->cmd, a[0] , a[1]), PIPE))))
				return (0);
			a[0] += a[1] + 1;
		}
		a[1] = find_char_not_escaped((*split)->cmd, '|', pipe_counter - 1);
		if (!(chunkadd(&to_insert,
			newchunk(ft_substr((*split)->cmd, a[1] + 1, ft_strlen((*split)->cmd) - a[1]), PIPE))))
			return (0);
		insert_list_in_list(split, &to_insert);
while (to_insert)
{
	printf("NEWCMD : %s\n", to_insert->cmd);
	to_insert = to_insert->next;
}
		while (*split && (*split)->sep_type == PIPE)
			split = &((*split)->next);
	}
	return (1);
}*/

t_cmdchunk	*split_line(char *line, char sep, int septype)
{
	unsigned int	semicol_counter;
	t_cmdchunk		*ret;
	unsigned int	i;
	long			a[2];

	semicol_counter = 0;
	while (find_char_not_escaped(line, sep, semicol_counter) != -1)
		semicol_counter++;
	i = -1;
	a[0] = 0;
	ret = NULL;
	while (++i < semicol_counter)
	{
		a[1] = find_char_not_escaped(&line[a[0]], sep, 0);
		if (!(chunkadd(&ret, newchunk(ft_substr(line, a[0] , a[1]), septype))))
			return (NULL);
		a[0] += a[1] + 1;
	}
	a[1] = find_char_not_escaped(line, sep, semicol_counter - 1);
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

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
	t_cmdchunk	*begin;
	t_cmdchunk	*pipe_split;
	int 			is_begin;

	split = split_line(line, ';', SEMICO);
	is_begin = 1;
	while (split)
	{
		printf("SEMICOLCMD: %s\n", split->cmd);

		pipe_split = split_line(split->cmd, '|', PIPE);

		t_cmdchunk *currpipe;
		currpipe = pipe_split;
		while (currpipe)
		{
			printf("\tPIPECMD : %s\n", currpipe->cmd);
			currpipe = currpipe->next;
		}
		replace_node_by_list(&split, &pipe_split);
		if (is_begin)
			begin = split;
		is_begin = 0;
printf("BEGIN IS NOW %s\n", (begin)->cmd);
		while (split && split->sep_type == PIPE)
		{

			printf("SKIPPING %s\n", split->cmd);

			split = split->next;
		}

		if (split)
			printf("NOW POINTING AT :%s\n", split->cmd);
		else
			printf("end reached\n");
	}
	return (begin);
}

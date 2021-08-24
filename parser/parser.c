/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:11:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 18:00:36 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include "parser.h"

int main(int argc, char **argv)
{
    (void)argc;
	(void)argv;
	t_cmdchunk 	*cmdc;
	t_cmdchunk	*tmp;
	t_chunkseg	*cs;
	t_chunkseg	*tmp2;
	char		*line;
	char		**segs;
	int	i;
	line = "";
	segs = NULL;
	while (line)
	{
		line = readline("prompt$ ");
		if (line)
		{
			add_history(line);
			//printf("%s\n%ld\n", line, fchar_nesc(line, '$', 4));
			printf("[%s]\n%d\n", line, count_all_segments(line));
			cmdc = chunk_list_creator(line);
			if (!cmdc)
				continue ;
			tmp = cmdc;
			cs = NULL;
			while (tmp)
			{
				chunkseg_builder(&cs, tmp);
				tmp = tmp->next;
			}
			chunksdel(cmdc);
			tmp2 = cs;
			while (tmp2)
			{
				i = 0;
				while (tmp2->segments[i])
				{
					printf("[%s]\n", tmp2->segments[i]);
					i++;
				}
				tmp2 = tmp2->next;
			}
			chunkseg_killer(cs);
		}
	}
	return (0);
}
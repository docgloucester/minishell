/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:11:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/25 13:27:10 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   include "parser.h"

int leaks_test(char *line);
int quotes_tests(char *str);

int main(int argc, char **argv)
{
    (void)argc;
	(void)argv;
	char		*line;
	char		**segs;
	line = "cat << x";
	segs = NULL;
	while (line)
	{
		// line = readline("prompt$ ");
		if (line)
		{
			// add_history(line);
			// printf("%s\n%ld\n", line, fchar_nesc(line, '$', 4));
			leaks_test(line);
			// quotes_tests(line);
		}
		break ;
	}
	return (0);
}

int quotes_tests(char *str)
{
	strip_quotes(str);
	
	// remove_char_from_str(str, '\\', 1, 1);
	printf("%s\n", str);
	return (0);
}

int leaks_test(char *line)
{
	int				i;
	t_cmdchunk 		*cmdc;
	t_cmdchunk		*tmp;
	t_chunkseg		*cs;
	t_chunkseg		*tmp2;
	t_cmdcontent	*ccon;
	t_ioitem		*tmp3;

	printf("[%s]\n%d\n", line, count_all_segments(line));
	cmdc = chunk_list_creator(line);
	if (!cmdc)
		return (0);
	tmp = cmdc;
	cs = NULL;
	i = 0;
	while (tmp)
	{
		if (chunkseg_builder(&cs, tmp) == -1)
		{
			chunkseg_killer(cs);
			chunksdel(cmdc);
			return (0);
		}
		tmp = tmp->next;
	}
	chunksdel(cmdc);
	tmp2 = cs;
	while (tmp2)
	{
		i = 0;
		while (tmp2->segments && tmp2->segments[i])
		{
			printf("[%s]\n", tmp2->segments[i]);
			i++;
		}
		tmp2 = tmp2->next;
	}
	cmdcontent_builder(&ccon, cs);
	cmdcontent_extract_iothings(ccon, cs);
	printf("\n");
	tmp3 = ccon->inputs;
	if (tmp3)
		printf("inputs:\n");
	while (tmp3)
	{
		printf("{[%d]::%s}\n", tmp3->type, tmp3->name);
		tmp3 = tmp3->next;
	}
	printf("\n");
	tmp3 = ccon->outputs;
	if (tmp3)
		printf("outputs:\n");
	while (tmp3)
	{
		printf("{[%d]::%s}\n", tmp3->type, tmp3->name);
		tmp3 = tmp3->next;
	}
	printf("\n");
	cmdcontent_extract_cmd(ccon, cs);
	i = 0;
	while (ccon->cmd && ccon->cmd[i])
	{
		printf("cmd[%s]\n", ccon->cmd[i]);
		i++;
	}
	chunkseg_killer(cs);
	cmdcontent_killer(ccon);
	return (0);
}
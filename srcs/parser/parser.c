/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:11:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/25 15:04:31 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int leaks_test(char *line);
int quotes_tests(char *str);

int mainn(int argc, char **argv)
{
    (void)argc;
	(void)argv;
	char		*line;
	char		**segs;
	line = "    ";
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
	t_cmdchunk 		*cmdc = NULL;
	t_cmdchunk		*tmp = NULL;
	t_chunkseg		*cs = NULL;
	t_chunkseg		*tmp2 = NULL;
	t_cmdcontent	*ccon = NULL;
	t_ioitem		*tmp3 = NULL;
	t_cmdcontent	*tmp4 = NULL;

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
	ccon = NULL;
	while (tmp2)
	{
		i = 0;
		while (tmp2->segments && tmp2->segments[i])
		{
			printf("[%s]\n", tmp2->segments[i]);
			i++;
		}
		cmdcontent_builder(&ccon, tmp2);
		tmp2 = tmp2->next;
	}
	printf("\n");
	tmp4 = ccon;
	while (tmp4)
	{
		printf("current cmdcontent:\n");
		tmp3 = tmp4->inputs;
		if (tmp3)
			printf("inputs:\n");
		while (tmp3)
		{
			printf("{[%d]::%s}\n", tmp3->type, tmp3->name);
			tmp3 = tmp3->next;
		}
		tmp3 = tmp4->outputs;
		if (tmp3)
			printf("outputs:\n");
		while (tmp3)
		{
			printf("{[%d]::%s}\n", tmp3->type, tmp3->name);
			tmp3 = tmp3->next;
		}
		i = 0;
		while (tmp4->cmd && tmp4->cmd[i])
		{
			printf("cmd[%s]\n", tmp4->cmd[i]);
			i++;
		}
		tmp4 = tmp4->next;
	}
	chunkseg_killer(cs);
	cmdcontent_killer(ccon);
	return (0);
}
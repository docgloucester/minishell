/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:11:31 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/27 11:33:37 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	cmdcontent_filler(t_chunkseg **cs, t_cmdcontent **ccon)
{
	t_chunkseg		*tmp;

	tmp = *cs;
	while (tmp)
	{
		if (cmdcontent_builder(ccon, tmp) == -1)
		{
			chunkseg_killer(*cs);
			cmdcontent_killer(*ccon);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	chunkseg_filler(t_cmdchunk **cmdc, t_chunkseg **cs)
{
	t_cmdchunk		*tmp;
	t_chunkseg		*tmp2;

	tmp = *cmdc;
	tmp2 = *cs;
	while (tmp)
	{
		if (chunkseg_builder(cs, tmp) == -1)
		{
			chunkseg_killer(*cs);
			chunksdel(*cmdc);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	first_parser(t_minishell *m, char *line)
{
	t_cmdchunk		*cmdc;
	t_chunkseg		*cs;
	t_cmdcontent	*ccon;

	cs = NULL;
	ccon = NULL;
	cmdc = chunk_list_creator(line);
	if (!cmdc)
		return (0);
	if (!chunkseg_filler(&cmdc, &cs))
		return (0);
	chunksdel(cmdc);
	if (!cmdcontent_filler(&cs, &ccon))
		return (0);
	chunkseg_killer(cs);
	if (ccon_to_exec(ccon, m) == -1)
	{
		exec_killer(m->ed);
		m->ed = NULL;
		return (0);
	}
	cmdcontent_killer(ccon);
	return (1);
}

int	second_parser(t_execdata *d, t_varenv *ve)
{
	int	i;
	int	cmdcount;

	i = 0;
	cmdcount = count_strs(d->cmd, 0);
	while (d->cmd[i])
	{
		if (d->type != INPUT_D)
			if (var_resolver(&d->cmd[i], ve) == -1)
				return (error_handler(NULL, NULL, -1));
		remove_char_from_str(d->cmd[i], '\\', 1, 1);
		strip_quotes(d->cmd[i]);
		i++;
	}
	remove_nullspaces(d->cmd, cmdcount);
	if (d->type == BINARY && is_builtin(d->cmd))
		d->type = BUILTIN;
	return (0);
}

// int parsing_tests(t_minishell *m, char *line)
// {
// 	int				i;
// 	t_cmdchunk 		*cmdc = NULL;
// 	t_cmdchunk		*tmp = NULL;
// 	t_chunkseg		*cs = NULL;
// 	t_chunkseg		*tmp2 = NULL;
// 	t_cmdcontent	*ccon = NULL;
// 	t_ioitem		*tmp3 = NULL;
// 	t_cmdcontent	*tmp4 = NULL;

	// printf("[%s]\n%d\n", line, count_all_segments(line));
	// cmdc = chunk_list_creator(line);
	// if (!cmdc)
	// 	return (0);
	// tmp = cmdc;
	// cs = NULL;
	// i = 0;
	// while (tmp)
	// {
	// 	if (chunkseg_builder(&cs, tmp) == -1)
	// 	{
	// 		chunkseg_killer(cs);
	// 		chunksdel(cmdc);
	// 		return (0);
	// 	}
	// 	tmp = tmp->next;
	// }
	// chunksdel(cmdc);
	// tmp2 = cs;
	// ccon = NULL;
	// while (tmp2)
	// {
		// i = 0;
		// while (tmp2->segments && tmp2->segments[i])
		// {
		// 	printf("[%s]\n", tmp2->segments[i]);
		// 	i++;
		// }
	// 	cmdcontent_builder(&ccon, tmp2);
	// 	tmp2 = tmp2->next;
	// }
	// printf("\n");
	// tmp4 = ccon;
	// while (tmp4)
	// {
	// 	printf("current cmdcontent:\n");
	// 	tmp3 = tmp4->inputs;
	// 	if (tmp3)
	// 		printf("inputs:\n");
	// 	while (tmp3)
	// 	{
	// 		printf("{[%d]::%s}\n", tmp3->type, tmp3->name);
	// 		tmp3 = tmp3->next;
	// 	}
	// 	tmp3 = tmp4->outputs;
	// 	if (tmp3)
	// 		printf("outputs:\n");
	// 	while (tmp3)
	// 	{
	// 		printf("{[%d]::%s}\n", tmp3->type, tmp3->name);
	// 		tmp3 = tmp3->next;
	// 	}
	// 	i = 0;
	// 	while (tmp4->cmd && tmp4->cmd[i])
	// 	{
	// 		printf("cmd[%s]\n", tmp4->cmd[i]);
	// 		i++;
	// 	}
	// 	tmp4 = tmp4->next;
	// }
// 	chunkseg_killer(cs);
// 	ccon_to_exec(ccon, m);
// 	cmdcontent_killer(ccon);
// 	return (0);
// }

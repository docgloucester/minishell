/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/25 15:19:35 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int parsing_tests(t_minishell *m, char *line);

void sig_reset_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//int	exec_maker(t_minishell *m, char *line)
//{
	/* fnct premier parsing */
//	return (0);
//}

/*int	mainb(int argc, char **argv, char **env)
{
	t_minishell		m;
	char			*line;

	(void)argv;
	(void)argc;
	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	line = "";
	signal(SIGQUIT, SIG_IGN);
	while (line)
	{
		signal(SIGINT, &sig_reset_prompt);
		line = readline("pasdebashing$ ");
		if (line && line[0]) // && !exec_maker(&m, line))
		{
			// add_history(line);
			// m.ve.bin_return = exec_loop(m.ed, &m.ve);
			// exec_killer(m.ed);
			m.ed = NULL;
		}
	}
	builtin_exit(m.ve.minishell_var, NULL);
	return (0);
}*/

int	main(int argc, char **argv, char **env)
{
	t_minishell		m;
	char			*line;

	(void)argv;
	(void)argc;
	/* BINARY & BUILTIN */
	// char	*bin[] = {"cmd", "arg", NULL};
	// char *cat[] = {"cat", NULL};
	// /* (D)INPUT & (D)OUTPUT */
	// char	*file[] = {"pathtofile", NULL};

	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	line = "ls";
	parsing_tests(&m, line);
	m.ve.bin_return = exec_loop(m.ed, &m.ve);

	builtin_exit(&m, NULL);
	return (0);
}

int parsing_tests(t_minishell *m, char *line)
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
	ccon_to_exec(ccon, m);
	cmdcontent_killer(ccon);
	return (0);
}
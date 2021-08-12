/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/12 14:25:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// int		main_test(int argc, char **argv, char **env)
// {
// 	// char *envc[2] = {"exit", NULL};
// 	// char *export[4] = {"export", NULL, "ABCabc=", NULL};
// 	// char *exportb[4] = {"export", "NULL=", "ABCabc", NULL};
// 	// char *cat[4] = {"cat", NULL, NULL, NULL};
// 	// char *echo[4] = {"echo", "-nnnnnnnn", "NULL", NULL};
// 	// char *grep[3] = {"grep", "SHELL", NULL};
// 	// char *ls[3] = {"ls", NULL, NULL};
// 	// char *exp[3] = {"ww", NULL, NULL};

// 	t_minishell m;
// 	m.ed = NULL;
// 	m.ve = varenv_construct(&m, env);
// 	m.ve.env_to_str = env_to_str(&m.ve);
// 	(void)argc;
// 	// printf("---->%d\n", ve.count);
// 	// exec_builder(&m.ed, cat, BINARY, 0);
// 	// exec_builder(&m.ed, export, BUILTIN, 0);
// 	// exec_builder(&m.ed, envc, BUILTIN, 0);
// 	// exec_builder(&d, exp, INPUT_D, 1);
// 	// exec_builder(&d, exp, OUTPUT, 1);
// 	// exec_builder(&d, ls, BINARY, 0);
// 	// exec_builder(&d, grep, BINARY, 0);
// 	// exec_builder(&d, expp, OUTPUT, 0);
// 	// exec_builder(&d, ls, BINARY, 0);

// 	m.ve.bin_return = exec_loop(m.ed, &m.ve);
// 	printf("---->%d\n", m.ve.count);
// 	printf("!!%d\n", m.ve.bin_return);
// 	//builtin_exit(m.ed, &m.ve);
// 	return (0);
// }

void sig_reset_prompt(int signal)
{
	printf("\n");
	(void)signal;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	exec_maker(t_minishell *m, char *line)
{
	t_cmd_cont		*parsed;
	t_list			**tmp;
	t_list			*translated;
	t_proc_command	*pc;
	t_list			*cursor;

	parsed = command_parsing(line);
	if (error_token(parsed->parsed_command))
	{
		printf("SHIIIT\n");
		free_cmd(parsed);
		return (1);
	}
	tmp = process_parsed_command(parsed);
	// int i = -1;
	// while (tmp[++i])
	// 	print_conmmand_id_lst(tmp[i]);
	// ft_lstclear(&(parsed->parsed_command), &free_command_id);
	translated = translate_cmd(tmp);
	// print_proc_cmd_lst(translated);
	cursor = translated;
	while (cursor)
	{
		pc = cursor->content;
		// print_conmmand_id_lst(pc->subsection);
		exec_builder(&m->ed, pc->subsection, pc->type, pc->pipe);
		// debug_execdata(m->ed);
		// printf("pre\n");
		// printf("post\n");
		// printf("AFTER\n");
		// print_proc_cmd_lst(m->ed->stocked_list);
		cursor = cursor->next;
	}
	// free_lst_lst(tmp);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell m;
	char	*line;

	(void)argv;
	(void)argc;
	ft_memset(&m, 0, sizeof(t_minishell));
	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	signal(SIGINT, &sig_reset_prompt);
	line = "";
	while (line)
	{
		line = readline("pasdebashing$ ");
		if (line && line[0] && !exec_maker(&m, line))
		{
			// print_proc_cmd_lst(m.ed->stocked_list);
			debug_execdata(m.ed);
			add_history(line);
			m.ve.bin_return = exec_loop(m.ed, &m.ve);
		}
	}
	builtin_exit(m.ve.minishell_var);
	return (0);
}

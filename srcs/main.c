/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/13 21:11:21 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void sig_reset_prompt(int signal)
{
	(void)signal;
	printf("\n");
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
		// print_proc_cmd_lst(m->ed->stocked_list);
		cursor = cursor->next;
	}
	// free_lst_lst(tmp);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		m;
	char			*line;

	(void)argv;
	(void)argc;
	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	line = "";
	while (line)
	{
		signal(SIGINT, &sig_reset_prompt);
		line = readline("pasdebashing$ ");
		if (line && line[0] && !exec_maker(&m, line))
		{
			// print_proc_cmd_lst(m.ed->stocked_list);
			// debug_execdata(m.ed);
			add_history(line);
			// debug_execdata(m.ed);
			m.ve.bin_return = exec_loop(m.ed, &m.ve);
			exec_killer(m.ed);
			m.ed = NULL;
		}
	}
	builtin_exit(m.ve.minishell_var, NULL);
	return (0);
}

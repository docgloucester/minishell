/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/25 17:28:14 by nouchata         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN);
	while (line)
	{
		signal(SIGINT, &sig_reset_prompt);
		line = readline("bâche$ ");
		if (line && line[0])
		{
			add_history(line);
			if (!first_parser(&m, line))
				continue ;
			m.ve.bin_return = exec_loop(m.ed, &m.ve);
			exec_killer(m.ed);
			m.ed = NULL;
		}
	}
	builtin_exit(m.ve.minishell_var, NULL);
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_minishell		m;
// 	char			*line;

// 	(void)argv;
// 	(void)argc;
// 	/* BINARY & BUILTIN */
// 	// char	*bin[] = {"cmd", "arg", NULL};
// 	char **cat = malloc(sizeof(char *) * 2);
// 	cat[0] = ft_strdup("x");
// 	cat[1] = NULL;
// 	// /* (D)INPUT & (D)OUTPUT */
// 	// char	*file[] = {"pathtofile", NULL};
// 	char **srcs = malloc(sizeof(char *) * 1);
// 	srcs[0] = NULL;

// 	m.ed = NULL;
// 	m.ve = varenv_construct(&m, env);
// 	m.ve.env_to_str = env_to_str(&m.ve);
// 	// line = "wjdfhvghu";

// 	exec_builder(&m.ed, srcs, BINARY, 1);
// 	exec_builder(&m.ed, cat, OUTPUT, 0);

// 	m.ve.bin_return = exec_loop(m.ed, &m.ve);

// 	builtin_exit(&m, NULL);
// 	return (0);
// }
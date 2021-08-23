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
	/* fnct premier parsing */
	return (0);
}

int	mainb(int argc, char **argv, char **env)
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
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		m;
	char			*line;

	(void)argv;
	(void)argc;
	/* BINARY & BUILTIN */
	// char	*bin[] = {"cmd", "arg", NULL};
	char *cat[] = {"cat", NULL};
	/* (D)INPUT & (D)OUTPUT */
	// char	*file = {"pathtofile", NULL};

	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	line = "";

	exec_builder(&m.ed, cat, BINARY, 0);

	m.ve.bin_return = exec_loop(m.ed, &m.ve);

	builtin_exit(&m, NULL);
	return (0);
}
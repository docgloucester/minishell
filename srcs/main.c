/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/27 12:19:55 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	pimped_prompt(char **line)
{
	char	pwd[81];

	ft_memset(pwd, 0, 81);
	if (!getcwd(pwd, 80))
		pwd[0] = '?';
	printf("✨ \033[1;33mbâche\033[1m:\033[1;35m%s\033[0m", pwd);
	if (line)
		*line = readline("$ ");
	return (0);
}

void	sig_reset_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	pimped_prompt(NULL);
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
		pimped_prompt(&line);
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
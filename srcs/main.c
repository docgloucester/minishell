/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/29 11:37:17 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

char	*pimped_prompt(t_minishell *m)
{
	int		i;
	char	pwd[151];

	i = 0;
	ft_memset(m->readline_prompt, 0, 301);
	ft_memcpy(&m->readline_prompt[i], \
	"✨ \033[1;33mbâche\033[1m:\033[1;35m", 30);
	i += 30;
	ft_memset(pwd, 0, 151);
	if (!getcwd(pwd, 150))
		ft_memcpy(pwd, "(path too long)", 16);
	ft_memcpy(&m->readline_prompt[i - 1], pwd, ft_strlen(pwd));
	i += ft_strlen(pwd);
	ft_memcpy(&m->readline_prompt[i - 1], "\033[0m$ ", 7);
	return (m->readline_prompt);
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
		line = readline(pimped_prompt(&m));
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
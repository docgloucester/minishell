/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:52:45 by marvin            #+#    #+#             */
/*   Updated: 2021/08/30 14:00:41 by nouchata         ###   ########.fr       */
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
	"\001\033[1;33m\002bache:\001\033[1m\002\001\033[1;35m\002", 30);
	i += 30;
	ft_memset(pwd, 0, 151);
	getcwd(pwd, 150);
	if (errno == ERANGE)
		ft_memcpy(pwd, "(path too long)", 15);
	if (errno == ENOENT)
		ft_memcpy(pwd, "(deleted)", 9);
	ft_memcpy(&m->readline_prompt[i], pwd, ft_strlen(pwd));
	i += ft_strlen(pwd);
	ft_memcpy(&m->readline_prompt[i], "\001\033[0m\002$ ", 9);
	return (m->readline_prompt);
}

void	sig_reset_prompt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_shlvl(t_minishell *m)
{
	char			**lvl;
	int				level;
	char			*line;
	int				i;

	lvl = var_value_finder(&m->ve, "SHLVL", 0);
	level = 1;
	i = -1;
	if (lvl && lvl[0])
	{
		while (lvl[0][++i] && ft_isdigit(lvl[0][i]))
			;
		if (lvl[0][i] == 0)
			level = ft_atoi(lvl[0]) + 1;
	}
	line = ft_strjoin("SHLVL=", ft_itoa(level));
	if (line)
		push_envitem(&m->ve, line);
	free(line);
}

void	run_prompt(t_minishell *m, char **line)
{
	signal(SIGINT, &sig_reset_prompt);
	free(*line);
	*line = readline(pimped_prompt(m));
	if (*line && (*line)[0])
	{
		add_history(*line);
		if (!first_parser(m, *line))
		{
			m->ve.bin_return = 2;
			return ;
		}
		m->ve.bin_return = exec_loop(m->ed, &m->ve);
		exec_killer(m->ed);
		m->ed = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		m;
	char			*line;

	(void)argv;
	(void)argc;
	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	set_shlvl(&m);
	m.ve.env_to_str = env_to_str(&m.ve);
	line = ft_strdup("");
	signal(SIGQUIT, SIG_IGN);
	while (line)
	{
		run_prompt(&m, &line);
	}
	builtin_exit(m.ve.minishell_var, NULL);
	return (0);
}

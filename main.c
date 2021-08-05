# include "minishell.h"

int		main_test(int argc, char **argv, char **env)
{
	char *envc[2] = {"exit", NULL};
	char *export[4] = {"export", NULL, "ABCabc=", NULL};
	char *exportb[4] = {"export", "NULL=", "ABCabc", NULL};
	char *cat[4] = {"cat", NULL, NULL, NULL};
	char *echo[4] = {"echo", "-nnnnnnnn", "NULL", NULL};
	char *grep[3] = {"grep", "SHELL", NULL};
	char *ls[3] = {"ls", NULL, NULL};
	char *exp[3] = {"ww", NULL, NULL};

	t_minishell m;
	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	// printf("---->%d\n", ve.count);
	exec_builder(&m.ed, cat, BINARY, 0);
	// exec_builder(&m.ed, export, BUILTIN, 0);
	// exec_builder(&m.ed, envc, BUILTIN, 0);
	// exec_builder(&d, exp, INPUT_D, 1);
	// exec_builder(&d, exp, OUTPUT, 1);
	// exec_builder(&d, ls, BINARY, 0);
	// exec_builder(&d, grep, BINARY, 0);
	// exec_builder(&d, expp, OUTPUT, 0);
	// exec_builder(&d, ls, BINARY, 0);

	m.ve.bin_return = exec_loop(m.ed, &m.ve);
	printf("---->%d\n", m.ve.count);
	printf("!!%d\n", m.ve.bin_return);
	//builtin_exit(m.ed, &m.ve);
	return (0);
}

void sig_reset_prompt(int signal)
{
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell m;
	char	*line;

	m.ed = NULL;
	m.ve = varenv_construct(&m, env);
	m.ve.env_to_str = env_to_str(&m.ve);
	line = "x";
	signal(SIGINT, &sig_reset_prompt);
	while (line)
	{
		line = readline("pasdebashing$ ");
		add_history(line);
	}
	builtin_exit(m.ve.minishell_var);
	return (0);
}
# include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char *envc[2] = {"env", NULL};
	char *export[4] = {"export", "aaaa", "ABCabc=", NULL};
	char *cat[4] = {"cat", NULL, NULL, NULL};
	char *grep[3] = {"grep", "SHELL", NULL};
	char *ls[3] = {"ls", NULL, NULL};
	char *exp[3] = {"ww", NULL, NULL};
	t_execdata *d = NULL;
	t_varenv ve = varenv_construct(env);
	ve.env_to_str = env_to_str(&ve);
	printf("---->%d\n", ve.count);
	exec_builder(&d, export, BUILTIN, 0);
	exec_builder(&d, envc, BUILTIN, 0);
	// exec_builder(&d, exp, INPUT_D, 1);
	// exec_builder(&d, exp, OUTPUT, 1);
	// exec_builder(&d, ls, BINARY, 0);
	// exec_builder(&d, grep, BINARY, 0);
	// exec_builder(&d, expp, OUTPUT, 0);
	// exec_builder(&d, ls, BINARY, 0);

	ve.bin_return = exec_loop(d, &ve);
	printf("---->%d\n", ve.count);
	printf("!!%d\n", ve.bin_return);
	varenv_kill(&ve);
	exec_killer(d);
	return (0);
}
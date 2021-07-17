# include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char *cat[4] = {"/bin/cat", NULL, NULL, NULL};
	char *grep[3] = {"/usr/bin/grep", NULL, NULL};
	char *ls[3] = {"/bin/ls", NULL, NULL};
	char *exp[3] = {"ww", NULL, NULL};
	char *expp[3] = {"_zz", NULL, NULL};
	t_execdata *d = NULL;
	t_varenv ve = varenv_construct(env);
	ve.env_to_str = env_to_str(&ve);

	exec_builder(&d, cat, BINARY, 1);
	// exec_builder(&d, exp, INPUT_D, 1);
	exec_builder(&d, exp, OUTPUT_D, 0);
	// exec_builder(&d, ls, BINARY, 0);
	// exec_builder(&d, grep, BINARY, 0);
	// exec_builder(&d, expp, OUTPUT, 0);
	// exec_builder(&d, ls, BINARY, 0);

	ve.bin_return = exec_loop(d, &ve);
	printf("!!%d\n", ve.bin_return);
	varenv_kill(&ve);
	exec_killer(d);
	return (0);
}
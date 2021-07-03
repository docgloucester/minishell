# include "exec.h"

void	signo(int signal)
{
	return ;
}

int		main(int argc, char **argv, char **env)
{
	char *cat[4] = {"/bin/cat", NULL, NULL, NULL};
	char *grep[3] = {"/usr/bin/grep", "x", NULL};
	char *ls[3] = {"/bin/ls", NULL, NULL};
	char *exp[3] = {"_ww", NULL, NULL};
	char *expp[3] = {"_zz", NULL, NULL};
	t_execdata *d = NULL;

	exec_builder(&d, cat, BINARY, 1);
	exec_builder(&d, exp, OUTPUT_D, 0);
	// exec_builder(&d, grep, BINARY, 0);
	// exec_builder(&d, expp, OUTPUT, 0);
	// exec_builder(&d, ls, BINARY, 0);
	signal(SIGINT, signo);
	printf("!!%d\n", exec_loop(d, env));
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:06:03 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/30 13:26:39 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <dirent.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <signal.h>
# include "../varenv/varenv.h"

typedef enum e_exectype
{
	BINARY,
	BUILTIN,
	OUTPUT,
	OUTPUT_D,
	INPUT,
	INPUT_D
}			t_exectype;

typedef struct s_execdata
{
	t_exectype			type;
	char				**cmd;
	pid_t				pid;
	int					pipes[2];
	char				pipe_on;
	int					return_v;
	struct s_execdata	*prec;
	struct s_execdata	*next;
}				t_execdata;

int		exec_builder(t_execdata **d, char **cmd, t_exectype type, char pipe);
int		exec_ret(t_execdata *d);
int		close_fd(int fd);
int		ft_kill(t_execdata *d, int sig, int retval);
int		var_setter(t_execdata *d, t_varenv *ve);
int		pipe_setter(t_execdata *d, int child);
int		bin_wrapper(t_execdata *d, t_varenv *ve);
int		search_in_path(t_execdata *d, t_varenv *ve);
int		export_wrapper(t_execdata *d, t_varenv *ve);
int		import_wrapper(t_execdata *d, t_varenv *ve);
int		interactive_wrapper(t_execdata *d, t_varenv *ve, int fdout);
int		cmd_dispatcher(t_execdata *d, t_varenv *ve);
int		exec_loop(t_execdata *d, t_varenv *ve);
void	ft_close(int *fd, int size);
int		exec_killer(t_execdata *d);
int		builtin_wrapper(t_execdata *d, t_varenv *ve);

#endif
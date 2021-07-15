/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:06:03 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 10:00:14 by nouchata         ###   ########.fr       */
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
# include "../_libft/libft.h"
# include "../varenv/varenv.h"

typedef enum e_execerror
{
	NO_ERROR,
	PIPE,
	FORK,
	DUP,
	READ,
	OPEN
}			t_execerror;

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
	t_execerror			error;
	struct s_execdata	*prec;
	struct s_execdata	*next;
}				t_execdata;

int		exec_builder(t_execdata **d, char **cmd, t_exectype type, char pipe);
int		close_fd(int fd);
int		find_ret_value(t_execdata *d);
int		var_setter(t_execdata *d);
int		pipe_setter(t_execdata *d, int child);
int		bin_wrapper(t_execdata *d, t_varenv *ve);
int		export_wrapper(t_execdata *d, t_varenv *ve);
int		import_wrapper(t_execdata *d, t_varenv *ve);
int		interactive_wrapper(t_execdata *d, t_varenv *ve);
int		cmd_dispatcher(t_execdata *d, t_varenv *ve);
int		exec_loop(t_execdata *d, t_varenv *ve);
void	ft_close(int *fd, int size);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:29:34 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/12 20:28:52 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	is_file_in_path(char *file, DIR *dir)
{
	struct dirent	*entity;

	entity = readdir(dir);
	while (entity)
	{
		if (!ft_strncmp(file, entity->d_name, 0))
			return (1);
		entity = readdir(dir);
	}
	return (0);
}

int	file_path_creator(t_execdata *d, char *path)
{
	char	*newpath;
	char	*new;

	newpath = ft_strjoin(path, "/");
	if (!newpath)
		return (-1);
	new = ft_strjoin(newpath, d->cmd[0]);
	if (!new)
		return (-1);
	free(newpath);
	// free(d->cmd[0]);
	d->cmd[0] = new;
	return (0);
}

int	search_in_path(t_execdata *d, t_varenv *ve)
{
	char	**paths;
	int		i;
	DIR		*dir;

	if (ft_strchr(d->cmd[0], '/'))
		return (0);
	paths = var_value_finder(ve, "PATH", 0);
	i = -1;
	dir = NULL;
	while (paths && paths[++i])
	{
		dir = opendir(paths[i]);
		if (!dir)
			continue ;
		if (is_file_in_path(d->cmd[0], dir))
		{
			closedir(dir);
			return (file_path_creator(d, paths[i]));
		}
		closedir(dir);
	}
	return (0);
}

int	bin_wrapper(t_execdata *d, t_varenv *ve)
{
	if (var_setter(d, ve) == -1)
		return (-1);
	if (d->pid)
	{
		pipe_setter(d, 0);
		if (d->pipe_on)
			if (cmd_dispatcher(d->next, ve) < 0)
				return (-1);
		if (!d->pipe_on)
			cmd_dispatcher(NULL, ve);
		waitpid(d->pid, &d->return_v, 0);
		ft_close(d->pipes, 2);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		if (pipe_setter(d, 1) == -1)
			exit(EXIT_FAILURE);
		if (execve(d->cmd[0], d->cmd, ve->env_to_str) == -1)
			exit(error_handler(NULL, d->cmd[0], EXIT_FAILURE));
	}
	return (0);
}

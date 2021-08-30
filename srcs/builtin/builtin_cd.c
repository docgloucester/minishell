/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:34:12 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/30 12:54:26 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	builtin_cd_editoldpwd(char *oldpwd, char *pwd, t_varenv *ve)
{
	char	*fpath;
	int		i;

	i = 0;
	fpath = ft_strjoin("PWD=", pwd);
	if (!fpath)
		return (error_handler("cd", NULL, -1));
	i = push_envitem(ve, fpath);
	free(fpath);
	if (i)
		return (error_handler_p("cd: failed to replace PWD", -1));
	fpath = ft_strjoin("OLDPWD=", oldpwd);
	if (!fpath)
		return (error_handler("cd", NULL, -1));
	i = push_envitem(ve, fpath);
	free(fpath);
	if (i)
		return (error_handler_p("cd: failed to replace OLDPWD", -1));
	return (0);
}

int	builtin_cd_dash(char **path, t_execdata *d, t_varenv *ve)
{
	char	dpath[501];
	int		i;

	i = 0;
	ft_memset(dpath, 0, 501);
	getcwd(dpath, 500);
	if (!path)
		return (error_handler_p("cd: OLDPWD not set", 1));
	i = chdir(path[0]);
	if (i == -1)
		return (error_handler("cd", path[0], 1));
	print_builtin(d, path[0]);
	if (builtin_cd_editoldpwd(dpath, path[0], ve) == -1)
		return (-1);
	print_builtin(d, "\n");
	return (0);
}

int	builtin_cd_home(char **path, t_varenv *ve)
{
	char	dpath[501];
	int		i;

	i = 0;
	ft_memset(dpath, 0, 501);
	getcwd(dpath, 500);
	if (!path)
		return (error_handler_p("cd: HOME not set", 1));
	i = chdir(path[0]);
	if (i == -1)
		return (error_handler("cd", path[0], 1));
	if (builtin_cd_editoldpwd(dpath, path[0], ve) == -1)
		return (-1);
	return (0);
}

int	builtin_cd(t_execdata *d, t_varenv *ve)
{
	int		ret;
	char	dpath[501];
	char	new_dpath[501];

	ret = 0;
	ft_memset(dpath, 0, 501);
	ft_memset(new_dpath, 0, 501);
	getcwd(dpath, 500);
	if (!d->cmd[1])
		return (builtin_cd_home(var_value_finder(ve, "HOME", 0), ve));
	if (d->cmd[1] && d->cmd[2])
		return (error_handler_p("cd: too many arguments" ,1));
	if (!ft_strlen(d->cmd[1]))
		return (0);
	if (!ft_strncmp(d->cmd[1], "-", 0))
		return (builtin_cd_dash(var_value_finder(ve, "OLDPWD", 0), d, ve));
	ret = chdir(d->cmd[1]);
	if (ret == -1)
		return (error_handler("cd", d->cmd[1], 1));
	getcwd(new_dpath, 500);
	if (builtin_cd_editoldpwd(dpath, new_dpath, ve) == -1)
		return (-1);
	return (0);
}

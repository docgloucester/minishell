/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:31:56 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/25 15:04:30 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	remove_char_from_str(char *str, char trm, int except_in_dbq, int x_in_q)
{
	int	i;
	int	j;
	int	dbqcnt;
	int	qcount;

	i = 0;
	j = 0;
	dbqcnt = 0;
	qcount = 0;
	while (str && str[i])
	{
		if ((i == 0 || str[i - 1] != '\\') && str[i] == '\"' && qcount % 2 == 0)
			dbqcnt++;
		if ((i == 0 || str[i - 1] != '\\') && str[i] == '\'' && dbqcnt % 2 == 0)
			qcount++;
		str[j] = str[i];
		i++;
		if (str[j] != trm || (except_in_dbq && dbqcnt % 2 != 0)
			|| (x_in_q && qcount % 2 != 0))
			j++;
	}
	while (j <= i)
		str[j++] = 0;
}

void	strip_quotes(char *str)
{
	int	i;
	int	j;
	int	dbqcnt;
	int	qcnt;

	i = 0;
	j = 0;
	dbqcnt = 0;
	qcnt = 0;
	while (str && str[i])
	{
		if ((i == 0 || str[i - 1] != '\\') && str[i] == '\"' && qcnt % 2 == 0)
			dbqcnt++;
		if ((i == 0 || str[i - 1] != '\\') && str[i] == '\'' && dbqcnt % 2 == 0)
			qcnt++;
		str[j] = str[i];
		if (!((str[i] == '\'' && dbqcnt % 2 == 0)
				|| (str[i] == '\"' && qcnt % 2 == 0)))
			j++;
		i++;
	}
	while (j <= i)
		str[j++] = 0;
}

void	remove_nullspaces(char **arr, int cmdcount)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr && i < cmdcount)
	{
		arr[j] = arr[i];
		i++;
		if (arr[j] != NULL)
			j++;
	}
	while (j <= i)
		arr[j++] = NULL;
}

int	is_builtin(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 0))
		return (1);
	if (!ft_strncmp(cmd[0], "cd", 0))
		return (1);
	if (!ft_strncmp(cmd[0], "pwd", 0))
		return (1);
	if (!ft_strncmp(cmd[0], "export", 0))
		return (1);
	if (!ft_strncmp(cmd[0], "unset", 0))
		return (1);
	if (!ft_strncmp(cmd[0], "env", 0))
		return (1);
	if (!ft_strncmp(cmd[0], "exit", 0))
		return (1);
	return (0);
}
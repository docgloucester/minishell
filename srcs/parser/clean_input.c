/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:31:56 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/27 11:22:34 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	remove_char_from_str(char *s, char trm, int x_in_dbq, int x_in_q)
{
	int	i;
	int	j;
	int	dbqcnt;
	int	qcount;

	i = 0;
	j = 0;
	dbqcnt = 0;
	qcount = 0;
	while (s && s[i])
	{
		if ((i == 0 || s[i - 1] != '\\') && s[i] == '\"' && qcount % 2 == 0)
			dbqcnt++;
		if ((i == 0 || s[i - 1] != '\\') && s[i] == '\'' && dbqcnt % 2 == 0)
			qcount++;
		s[j] = s[i];
		i++;
		if (s[j] != trm || (x_in_dbq && dbqcnt % 2 != 0 && s[j + 1] != '$')
			|| (x_in_q && qcount % 2 != 0))
			j++;
	}
	while (s && j <= i)
		s[j++] = 0;
}

void	strip_quotes(char *s)
{
	int	i;
	int	j;
	int	dbqcnt;
	int	qcnt;

	i = 0;
	j = 0;
	dbqcnt = 0;
	qcnt = 0;
	while (s && s[i])
	{
		if ((i == 0 || s[i - 1] != '\\') && s[i] == '\"' && qcnt % 2 == 0)
			dbqcnt++;
		if ((i == 0 || s[i - 1] != '\\') && s[i] == '\'' && dbqcnt % 2 == 0)
			qcnt++;
		s[j] = s[i];
		if (!((s[i] == '\'' && dbqcnt % 2 == 0)
				|| (s[i] == '\"' && qcnt % 2 == 0)))
			j++;
		i++;
	}
	while (s && j <= i)
		s[j++] = 0;
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
	if (!cmd || !cmd[0])
		return (0);
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

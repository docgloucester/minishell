/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:19:37 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 09:22:19 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int		test_dir(char *path, char *cmd, int print_error)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid)
		waitpid(pid, &status, 0);
	if (!pid)
	{
		status = chdir(path);
		if (status && print_error)
			error_handler(cmd, path, status);
		exit(status);
	}
	return (WEXITSTATUS(status));
}

int		search_in_dir(char *path)
{
	return (0);
}
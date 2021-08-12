/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:04:42 by marvin            #+#    #+#             */
/*   Updated: 2021/08/12 16:59:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *check)
{
	if (!check)
		return (0);
	if (!ft_strncmp(check, "echo", ft_strlen(check))
		|| !ft_strncmp(check, "cd", ft_strlen(check))
		|| !ft_strncmp(check, "pwd", ft_strlen(check))
		|| !ft_strncmp(check, "export", ft_strlen(check))
		|| !ft_strncmp(check, "unset", ft_strlen(check))
		|| !ft_strncmp(check, "env", ft_strlen(check))
		|| !ft_strncmp(check, "exit", ft_strlen(check)))
		return (1);
	return (0);
}

void	find_builtin(t_execdata **to_clean)
{
	t_execdata	*cursor;

	cursor = *to_clean;
	while (cursor)
	{
		if (is_builtin(cursor->cmd[0]))
			cursor->type = BUILTIN;
		cursor = cursor->next;
	}
}

void	exec_cleaner(void *m, t_execdata **to_clean)
{
	t_execdata	*cursor;

	cursor = *to_clean;
	while (cursor)
	{
		clean_section(cursor->stocked_list, m);
		cursor->cmd = create_cmd(cursor->stocked_list);
		cursor = cursor->next;
	}
	find_builtin(to_clean);
}

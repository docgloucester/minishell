/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_command_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:35:54 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:27:41 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

t_proc_command	*proc_command_create(char **cmd, int type, int pipe)
{
	t_proc_command	*ret;

	ret = malloc(sizeof(t_proc_command));
	if (!ret)
		exit(1);
	ret->cmd = cmd;
	ret->pipe = pipe;
	ret->type = type;
	return (ret);
}

t_list	*proc_command_create_lst_element(char **cmd, int type, int pipe)
{
	t_proc_command	*tmp;

	tmp = proc_command_create(cmd, type, pipe);
	return (ft_lstnew(tmp));
}

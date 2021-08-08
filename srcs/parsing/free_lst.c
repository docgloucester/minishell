/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:46:34 by marvin            #+#    #+#             */
/*   Updated: 2021/08/08 15:31:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_parsing.h"

void	free_cmd(t_cmd_cont *to_free)
{
	free(to_free->source_command);
	ft_lstclear(&(to_free->parsed_command), &free_command_id);
	free(to_free);
}

void	free_proc_cmd(void *to_clean)
{
	t_proc_command	*cast;
	t_list			*lst;

	lst = to_clean;
	cast = lst->content;
	free_str_table(cast->cmd);
	ft_lstclear(&lst, &free_command_id);
	free(lst);
}

void	free_proc_cmd_lst(t_list *to_free)
{
	ft_lstclear(&to_free, &free_proc_cmd);
}

void	free_lst_lst(t_list **to_free)
{
	int	i;

	i = -1;
	while (to_free[++i])
		ft_lstclear(&(to_free[i]), &free_command_id);
	free(to_free);
}

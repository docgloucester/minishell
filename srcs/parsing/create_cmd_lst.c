/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:51:42 by marvin            #+#    #+#             */
/*   Updated: 2021/08/12 13:55:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_parsing.h"

void	create_cmd_lst(t_list **lst, t_list *to_trans)
{
	t_command_id	*cast;

	while (to_trans)
	{
		cast = to_trans->content;
		if (!*lst)
			*lst = ft_lstnew(create_proc_command(to_trans));
		else
			ft_lstadd_back(lst, ft_lstnew(create_proc_command(to_trans)));
		if (cast->id == SEP)
			to_trans = to_trans->next;
		go_to_sep(&to_trans);
		if (to_trans)
		{
			cast = to_trans->content;
			if(cast->id == SEP && (!ft_strncmp(cast->value, "|", 1)))
				to_trans = to_trans->next;
		}
	}
}

void	go_to_sep(t_list **to_translate)
{
	t_command_id	*cast;

	if (*to_translate)
		cast = (*to_translate)->content;
	while (*to_translate && cast->id != SEP)
	{
		(*to_translate) = (*to_translate)->next;
		if (*to_translate)
			cast = (*to_translate)->content;
	}
}

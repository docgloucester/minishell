/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parsed_command_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:45:56 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/06 16:27:45 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	erase_last_commad_id_lst(t_list *lst)
{
	t_list	*first;
	t_list	*second;

	first = lst;
	if (!lst->next)
		return ;
	second = first->next;
	while (second->next)
	{
		first = first->next;
		second = second->next;
	}
	// free_command_id(&second);
	first->next = NULL;
}

int	is_command_id_value_sep(t_command_id *t)
{
	if (!ft_strncmp(t->value, ";", 1) || !ft_strncmp(t->value, "|", 1))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:04:42 by marvin            #+#    #+#             */
/*   Updated: 2021/08/06 17:53:01 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	exec_cleaner(void *m, t_list **to_clean)
{
	t_list			*cursor;
	t_proc_command	*cast;

	cursor = *to_clean;
	while (cursor)
	{
		cast = cursor->content;
		clean_section(&(cast->subsection), m);
		cast->cmd = create_cmd(cast->subsection);
		cursor = cursor->next;
	}
}

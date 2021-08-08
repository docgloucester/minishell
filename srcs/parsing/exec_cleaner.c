/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:04:42 by marvin            #+#    #+#             */
/*   Updated: 2021/08/08 20:06:14 by marvin           ###   ########.fr       */
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

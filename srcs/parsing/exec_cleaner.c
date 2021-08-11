/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:04:42 by marvin            #+#    #+#             */
/*   Updated: 2021/08/09 13:13:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	exec_cleaner(void *m, t_execdata **to_clean)
{
	t_execdata	*cursor;

	cursor = *to_clean;
	while (cursor)
	{
		clean_section(cursor->stocked_list, m);
		cursor->cmd =  create_cmd(cursor->stocked_list);
		cursor = cursor->next;
	}
}

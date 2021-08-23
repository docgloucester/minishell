/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkseg_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:44:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/23 17:14:44 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

int		chunkseg_builder(t_chunkseg **cs, t_cmdchunk *cmdc)
{
	t_chunkseg	*new;
	(void)cs;

	new = malloc(sizeof(t_chunkseg) * 1);
	if (!new)
		return (-1);
	new->sep_type = cmdc->sep_type;
	if (remove_spaces(&cmdc->cmd, 1) == -1)
	{
		free(new);
		return (-1);
	}
	return (0);
}
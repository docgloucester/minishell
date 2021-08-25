/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkseg_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:44:43 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/25 15:04:34 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int		chunkset_list_setup(t_chunkseg **cs, t_chunkseg *new)
{
	t_chunkseg	*old;

	old = *cs;
	while (old && old->next)
		old = old->next;
	if (old)
	{
		old->next = new;
		new->prev = old;
	}
	else
		*cs = new;
	return (0);
}

int		chunkseg_builder(t_chunkseg **cs, t_cmdchunk *cmdc)
{
	t_chunkseg	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_chunkseg) * 1);
	if (!new)
		return (-1);
	new->segments = extract_segments(cmdc->cmd);
	if (!new->segments)
	{
		free(new);
		return (-1);
	}
	new->segs_count = count_strs(new->segments, 0);
	new->sep_type = cmdc->sep_type;
	new->next = NULL;
	new->prev = NULL;
	chunkset_list_setup(cs, new);
	return (0);
}

int		chunkseg_killer(t_chunkseg *cs)
{
	t_chunkseg	*current;

	while (cs)
	{
		current = cs;
		cs = cs->next;
		current->segments = kill_segments(current->segments, \
		current->segs_count);
		free(current);
	}
	return (0);
}
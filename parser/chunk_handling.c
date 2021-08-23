/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:36:00 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/23 15:36:01 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmdchunk	*newchunk(char *str, int sep)
{
	t_cmdchunk	*new;

	new = malloc(sizeof(t_cmdchunk));
	if (!new)
		return (NULL);
	new->cmd = str;
	new->sep_type = sep;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	chunkadd(t_cmdchunk **chunklist, t_cmdchunk *new)
{
	t_cmdchunk	*chunk;

	if (!(chunklist))
		return (0);
printf("adding block with content %s\n", new->cmd);
	if (*chunklist)
	{
		chunk = *chunklist;
		while (chunk->next)
			chunk = chunk->next;
		chunk->next = new;
		chunk->next->prev = chunk;
	}
	else
		*chunklist = new;
	return (1);
}
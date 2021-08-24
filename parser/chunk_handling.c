/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:36:00 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/23 17:53:11 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmdchunk	*newchunk(char *str, char sep)
{
	t_cmdchunk	*new;

	new = malloc(sizeof(t_cmdchunk));
	if (!new)
		return (NULL);
	new->cmd = str;
	if (sep)
		new->sep_type = sep;
	else
		new->sep_type = ';';
	new->next = NULL;
	return (new);
}

int	chunkadd(t_cmdchunk **chunklist, t_cmdchunk *new)
{
	t_cmdchunk	*chunk;

	if (!(new))
		return (0);
	if (*chunklist)
	{
		chunk = *chunklist;
		while (chunk->next)
			chunk = chunk->next;
		chunk->next = new;
	}
	else
		*chunklist = new;
	return (1);
}

void	chunkdel(t_cmdchunk *node_to_del)
{
	if (node_to_del)
	{
		free(node_to_del->cmd);
		free(node_to_del);
	}
}

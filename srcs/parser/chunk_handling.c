/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:36:00 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/25 15:04:35 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

t_cmdchunk	*newchunk(char *str, char sep)
{
	t_cmdchunk	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_cmdchunk));
	if (!new)
	{
		free(str);
		return (NULL);
	}
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

void	chunksdel(t_cmdchunk *list_to_del)
{
	t_cmdchunk	*next;

	while (list_to_del)
	{
		next = list_to_del->next;
		free(list_to_del->cmd);
		free(list_to_del);
		list_to_del = next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcontent_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:55:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 18:02:57 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

// int		cmdcontent_io_transfert(t_cmdcontent *ccon, char **cmds, int i)
// {
// 	if (!cmds[i + 1])
// 		return (-1);
	
// }

// int		cmdcontent_extract_iothings(t_cmdcontent *ccon, t_chunkseg *cs)
// {
// 	int		i;

// 	i = 0;
// 	while (i < cs->segs_count)
// 	{
// 		if (!ft_strncmp(cs->segments[i], "<", 1) || \
// 		!ft_strncmp(cs->segments[i], "<<", 1) || \
// 		!ft_strncmp(cs->segments[i], ">", 1) || \
// 		!ft_strncmp(cs->segments[i], ">>", 1))
// 		{
// 			if (cmdcontent_io_transfert(ccon, cs, i) == -1)
// 				return (-1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int		cmdcontent_builder(t_cmdcontent **ccon, t_chunkseg *cs)
// {
// 	t_cmdcontent	*new;

// 	new->inputs = NULL;
// 	new->outputs = NULL;
// 	new->cmd = NULL;
// 	new->next = NULL;
// 	new->prev = NULL;
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcontent_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:55:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/25 13:31:49 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

int		ioitem_list_setup(t_cmdcontent *curr, t_ioitem *ioitem)
{
	t_ioitem	*tmp;

	tmp = NULL;
	if ((ioitem->type == IN || ioitem->type == DIN) && !curr->inputs)
		curr->inputs = ioitem;
	else if ((ioitem->type == IN || ioitem->type == DIN) && curr->inputs)
	{
		tmp = curr->inputs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ioitem;
		ioitem->prev = tmp;
	}
	if ((ioitem->type == OUT || ioitem->type == DOUT) && !curr->outputs)
		curr->outputs = ioitem;
	else if ((ioitem->type == OUT || ioitem->type == DOUT) && curr->outputs)
	{
		tmp = curr->outputs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ioitem;
		ioitem->prev = tmp;
	}
	return (0);
}

int		ioitem_builder(t_cmdcontent *curr, char *str, char *content)
{
	t_ioitem	*ioitem;

	ioitem = malloc(sizeof(t_ioitem) * 1);
	if (!ioitem)
		return (-1);
	ioitem->next = NULL;
	ioitem->prev = NULL;
	if (!ft_strncmp(str, "<<", 2))
		ioitem->type = DIN;
	else if (!ft_strncmp(str, "<", 1))
		ioitem->type = IN;
	else if (!ft_strncmp(str, ">>", 2))
		ioitem->type = DOUT;
	else if (!ft_strncmp(str, ">", 1))
		ioitem->type = OUT;
	ioitem->name = ft_strdup(content);
	if (!ioitem->name)
	{
		free(ioitem);
		return (-1);
	}
	ioitem_list_setup(curr, ioitem);
	return (0);
}

void	cmdcontent_killer(t_cmdcontent *ccon)
{
	t_cmdcontent	*tmp;
	t_ioitem		*tmpio;

	tmp = NULL;
	while (ccon)
	{
		printf("zzzz\n");
		tmp = ccon;
		kill_segments(tmp->cmd, 0);
		while (ccon->inputs)
		{
			tmpio = ccon->inputs;
			free(tmpio->name);
			ccon->inputs = tmpio->next;
			free(tmpio);
		}
		while (ccon->outputs)
		{
			tmpio = ccon->outputs;
			free(tmpio->name);
			ccon->outputs = tmpio->next;
			free(tmpio);
		}
		ccon = tmp->next;
		free(tmp);
	}
}

int		cmdcontent_builder(t_cmdcontent **ccon, t_chunkseg *cs)
{
	t_cmdcontent	*new;
	t_cmdcontent	*tmp;

	tmp = *ccon;
	new = malloc(sizeof(t_cmdcontent) * 1);
	if (!new)
		return (-1);
	new->next = NULL;
	new->prev = NULL;
	new->inputs = NULL;
	new->outputs = NULL;
	new->sep_type = cs->sep_type;
	new->cmd = NULL;
	*ccon = new;
	return (0);
}
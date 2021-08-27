/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcontent_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:55:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/27 11:05:35 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	ioitem_list_setup(t_cmdcontent *curr, t_ioitem *ioitem)
{
	t_ioitem	*tmp;

	tmp = NULL;
	if ((ioitem->type == in || ioitem->type == din) && !curr->inputs)
		curr->inputs = ioitem;
	else if ((ioitem->type == in || ioitem->type == din) && curr->inputs)
	{
		tmp = curr->inputs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ioitem;
		ioitem->prev = tmp;
	}
	if ((ioitem->type == out || ioitem->type == dout) && !curr->outputs)
		curr->outputs = ioitem;
	else if ((ioitem->type == out || ioitem->type == dout) && curr->outputs)
	{
		tmp = curr->outputs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = ioitem;
		ioitem->prev = tmp;
	}
	return (0);
}

int	ioitem_builder(t_cmdcontent *curr, char *str, char *content)
{
	t_ioitem	*ioitem;

	ioitem = malloc(sizeof(t_ioitem) * 1);
	if (!ioitem)
		return (error_handler(NULL, NULL, -1));
	ioitem->next = NULL;
	ioitem->prev = NULL;
	if (!ft_strncmp(str, "<<", 2))
		ioitem->type = din;
	else if (!ft_strncmp(str, "<", 1))
		ioitem->type = in;
	else if (!ft_strncmp(str, ">>", 2))
		ioitem->type = dout;
	else if (!ft_strncmp(str, ">", 1))
		ioitem->type = out;
	ioitem->name = ft_strdup(content);
	if (!ioitem->name)
	{
		free(ioitem);
		return (error_handler(NULL, NULL, -1));
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

int	cmdcontent_list_setup(t_cmdcontent **ccon, t_cmdcontent *new)
{
	t_cmdcontent	*tmp;

	tmp = *ccon;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		*ccon = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
	return (0);
}

int	cmdcontent_builder(t_cmdcontent **ccon, t_chunkseg *cs)
{
	t_cmdcontent	*new;
	t_cmdcontent	*tmp;

	if (!cs)
		return (0);
	tmp = *ccon;
	new = malloc(sizeof(t_cmdcontent) * 1);
	if (!new)
		return (error_handler(NULL, NULL, -1));
	new->next = NULL;
	new->prev = NULL;
	new->inputs = NULL;
	new->outputs = NULL;
	new->sep_type = cs->sep_type;
	new->cmd = NULL;
	if (cmdcontent_extract_iothings(new, cs) == -1 || \
	cmdcontent_extract_cmd(new, cs) == -1)
	{
		cmdcontent_killer(new);
		return (-1);
	}
	cmdcontent_list_setup(ccon, new);
	return (0);
}

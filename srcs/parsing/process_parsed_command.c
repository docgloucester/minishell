/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parsed_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:03:20 by tor               #+#    #+#             */
/*   Updated: 2021/08/12 11:10:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	handle_semi_colon(t_list **to_proc)
{
	int				i;
	t_command_id	*last;

	i = -1;
	while (to_proc[++i])
	{
		last = (ft_lstlast(to_proc[i]))->content;
		if (is_semi_colon(last))
			erase_last_commad_id_lst(to_proc[i]);
	}
}

t_list	*copy_cmd_id_lst(t_list **copy)
{
	t_list			*ret;
	t_command_id	*c;

	c = (*copy)->content;
	if (is_pipe((*copy)->content))
		*copy = (*copy)->next;
	ret = ft_lstnew((*copy)->content);
	if (*copy)
		(*copy) = (*copy)->next;
	if (*copy)
		c = (*copy)->content;
	while ((*copy) && !is_command_id_value_sep(c))
	{
		ft_lstadd_back(&ret, ft_lstnew(c));
		(*copy) = (*copy)->next;
		if ((*copy))
			c = (*copy)->content;
	}
	if (*copy && c->id == SEP && is_command_id_value_sep((*copy)->content))
		ft_lstadd_back(&ret, ft_lstnew(c));
	return (ret);
}

t_list	**split_lst(t_list *to_split)
{
	t_list	**splited;
	t_list	*c;
	int		size;
	int		i;

	size = count_sep_lst(to_split) + 2;
	splited = malloc(sizeof(t_list *) * size);
	if (!splited)
		exit(1);
	splited[0] = copy_cmd_id_lst(&to_split);
	splited[size - 1] = NULL;
	c = to_split;
	i = 0;
	while (c)
	{
		if (c && is_command_id_value_sep((t_command_id *)c->content))
			splited[++i] = copy_cmd_id_lst(&c);
		while (c && !is_command_id_value_sep((t_command_id *)c->content))
			c = c->next;
	}
	return (splited);
}

t_list	**process_parsed_command(t_cmd_cont *command_parsed)
{
	t_list			**tmp;

	tmp = split_lst(command_parsed->parsed_command);
	handle_semi_colon(tmp);
	return (tmp);
}

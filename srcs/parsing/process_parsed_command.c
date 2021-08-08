/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parsed_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:03:20 by tor               #+#    #+#             */
/*   Updated: 2021/08/08 10:55:57 by marvin           ###   ########.fr       */
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

// void	track_pipe(t_list **to_track)
// {
// 	int				i;
// 	t_command_id	*tmp;

// 	i = -1;
// 	while (to_track[++i])
// 	{
// 		tmp = (ft_lstlast(to_track[i]))->content;
// 		if (!ft_strncmp(tmp->value, "|", 1))
// 			ft_lstadd_front(&to_track[i + 1], command_id_create("|", SEP));
// 	}
// }

t_list	*copy_cmd_id_lst(t_list **to_copy)
{
	t_list			*ret;
	t_command_id	*cast;

	ret = ft_lstnew((*to_copy)->content);
	(*to_copy) = (*to_copy)->next;
	cast = (*to_copy)->content;
	while ((*to_copy) && !is_command_id_value_sep(cast))
	{
		ft_lstadd_back(&ret, ft_lstnew(cast));
		(*to_copy) = (*to_copy)->next;
		if ((*to_copy))
			cast = (*to_copy)->content;
	}
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
	// track_pipe(tmp);
	handle_semi_colon(tmp);
	return (tmp);
}

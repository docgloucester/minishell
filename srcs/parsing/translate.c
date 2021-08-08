/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:14:19 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/08 19:51:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	free_translate(t_list *to_free)
{
	t_proc_command	*cast;
	t_list			*cursor;

	cursor = to_free;
	while (cursor)
	{
		cast = cursor->content;
		free_str_table(cast->cmd);
		cursor = cursor->next;
	}
	ft_lstclear(&to_free, &free);
}

void	free_to_split(t_list *to_free)
{
	t_list			*cursor;
	t_command_id	*cast;

	cursor = to_free;
	print_conmmand_id_lst(to_free);
	while (cursor)
	{
		cast = cursor->content;
		free(cast->value);
		cursor = cursor->next;
	}
	ft_lstclear(&to_free, &free);
}

t_list	*split_builder_cmd(t_list *to_split)
{
	t_command_id	*cast;
	t_list			*splited;

	cast = to_split->content;
	splited = NULL;
	if (cast->id == SEP)
	{
		to_split = to_split->next;
		cast = to_split->content;
	}
	while (to_split && cast->id != SEP)
	{
		if (!splited)
			splited = ft_lstnew(cast);
		else
			ft_lstadd_back(&splited, ft_lstnew(cast));
		to_split = to_split->next;
		if (to_split)
			cast = to_split->content;
	}
	return (splited);
}

t_proc_command	*create_proc_command(t_list *to_translate)
{
	t_proc_command	*ret;

	ret = malloc(sizeof(t_proc_command));
	if (!ret)
		exit(1);
	ret->cmd = NULL;
	ret->pipe = set_pipe(&to_translate);
	ret->type = set_type_parsing(to_translate);
	ret->subsection = split_builder_cmd(to_translate);
	return (ret);
}

t_list	*translate_cmd(t_list **to_translate)
{
	t_list		*cmd_lst;
	int			i;

	cmd_lst = NULL;
	i = -1;
	while (to_translate[++i])
		create_cmd_lst(&cmd_lst, to_translate[i]);
	return (cmd_lst);
}

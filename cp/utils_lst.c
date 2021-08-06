/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:20:40 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:28:08 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	lst_size(t_list *to_count)
{
	int	i;

	if (!to_count)
		return (0);
	i = 1;
	while (to_count->next)
	{
		i++;
		to_count = to_count->next;
	}
	return (i);
}

int	find_first_sep_lst(t_list *to_parse)
{
	t_command_id	*cast;
	t_list			*cursor;
	int				res;

	res = 0;
	cursor = to_parse;
	cast = cursor->content;
	while (cursor && cast->id != SEP)
	{
		cursor = cursor->next;
		cast = cursor->content;
		res++;
	}
	return (res);
}

int	count_sep_lst(t_list *to_count)
{
	t_list			*cursor;
	t_command_id	*cast;
	int				ret;

	cursor = to_count;
	ret = 0;
	while (cursor)
	{
		cast = cursor->content;
		if (!ft_strncmp(cast->value, ";", 1)
			|| !ft_strncmp(cast->value, "|", 1))
			ret++;
		cursor = cursor->next;
	}
	return (ret);
}

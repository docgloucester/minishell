/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:44:18 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/08 11:03:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	free_command_id_element(t_list **to_free)
{
	t_command_id	*cast;

	cast = (*to_free)->content;
	free(cast->value);
	free((*to_free)->content);
	free(*to_free);
}

int	is_pipe(t_command_id *to_check)
{
	if (to_check->id == SEP && !ft_strncmp(to_check->value, "|", 1))
		return (1);
	return (0);
}

int	set_pipe(t_list **to_proc)
{
	t_list	*first;
	t_list	*last;
	t_list	*tmp;
	int		ret;

	first = (*to_proc);
	last = ft_lstlast(*to_proc);
	ret = 0;
	if (is_pipe(first->content))
	{
		tmp = first->next;
		// free_command_id(&first);
		(*to_proc) = tmp;
		ret = 1;
	}
	if (is_pipe(last->content))
		ret = 1;
	return (ret);
}

int	set_type_parsing(t_list *last)
{
	t_command_id	*c;

	c = last->content;
	if (c->id == SEP && !(ft_strncmp(c->value, ">", ft_strlen(c->value))))
		return (OUTPUT);
	else if (c->id == SEP && !(ft_strncmp(c->value, "<", ft_strlen(c->value))))
		return (INPUT);
	else if (c->id == SEP && !(ft_strncmp(c->value, ">>", ft_strlen(c->value))))
		return (OUTPUT_D);
	else if (c->id == SEP && !(ft_strncmp(c->value, "<<", ft_strlen(c->value))))
		return (INPUT_D);
	return (BINARY);
}

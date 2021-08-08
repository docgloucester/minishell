/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_command_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:09:21 by tor               #+#    #+#             */
/*   Updated: 2021/08/08 11:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	free_command_id(void *to_free)
{
	t_command_id	*cast;

	cast = to_free;
	free(cast->value);
	cast->value = NULL;
}

t_list	*command_id_create(char *value, int id)
{
	t_command_id	*tmp;

	tmp = malloc(sizeof(t_command_id));
	if (!tmp)
		exit(1);
	tmp->value = ft_strdup(value);
	tmp->id = id;
	return (ft_lstnew(tmp));
}

int	is_semi_colon(t_command_id *t)
{
	if (!ft_strncmp(t->value, ";", 1))
		return (1);
	return (0);
}

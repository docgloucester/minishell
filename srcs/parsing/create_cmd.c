/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 15:01:37 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/12 13:22:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	count_cmd_size(t_list *to_count)
{
	t_command_id	*cast;
	int				i;

	cast = NULL;
	if (to_count)
		cast = to_count->content;
	i = 0;
	if (cast && cast->id == SEP)
		to_count = to_count->next;
	while (to_count && cast->id != SEP)
	{
		cast = to_count->content;
		if (cast->id == END_OF_ARG)
			i++;
		to_count = to_count->next;
	}
	return (i + 1);
}

char	*create_arg(t_list **to_translate)
{
	char			*arg;
	t_command_id	*cast;
	char			*tmp;

	arg = NULL;
	cast = (*to_translate)->content;
	while (*to_translate && cast->id != END_OF_ARG && cast->id != SEP)
	{
		tmp = arg;
		if (!cast->value)
			arg = NULL;
		else if (!arg)
			arg = ft_strdup(cast->value);
		else if (arg)
			arg = ft_strjoin(arg, cast->value);
		free(tmp);
		(*to_translate) = (*to_translate)->next;
		if (*to_translate)
			cast = (*to_translate)->content;
	}
	if (cast->id == END_OF_ARG)
		(*to_translate) = (*to_translate)->next;
	return (arg);
}

char	**create_cmd(t_list *to_translate)
{
	int				size;
	char			**cmd;
	t_command_id	*cast;
	int				i;

	size = count_cmd_size(to_translate);
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		exit(1);
	i = 0;
	if (to_translate)
		cast = to_translate->content;
	while (i < size && to_translate && cast->id != SEP)
	{
		cast = to_translate->content;
		cmd[i] = create_arg(&to_translate);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:56:12 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/06 18:05:11 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_backslash(t_command_id *to_clean)
{
	char	*tmp;

	tmp = to_clean->value;
	to_clean->value = ft_strtrim(to_clean->value, "\\");
	free(tmp);
}

void	clean_quotes(t_command_id *to_clean)
{
	char	*tmp;

	tmp = to_clean->value;
	if (to_clean->id == QUOTES_S)
	{
		to_clean->value = ft_strtrim(to_clean->value, "'");
		free(tmp);
	}
	if (to_clean->id == QUOTES_D)
	{
		//env_translation
		to_clean->value = ft_strtrim(to_clean->value, "\"");
		free(tmp);
	}
}

void	clean_section(t_list **to_clean, void *m)
{
	t_list			*cursor;
	t_command_id	*cast;
	char			**var;
	t_minishell		*minishell;

	cursor = *to_clean;
	minishell = m;
	while (cursor)
	{
		cast = cursor->content;
		if (cast->id == QUOTES_S || cast->id == QUOTES_D)
			clean_quotes(cast);
		if (cast->id == BACKSLASH)
			clean_backslash(cast);
		if (cast->id == ENV)
		{
			var = var_value_finder(&minishell->ve, &cast->value[1], 1);
			free(cast->value);
			cast->value = var[0];
			free(var);
		}
		cursor = cursor->next;
	}
}

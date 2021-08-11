/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:56:12 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/09 11:04:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_transaltion_d_quotes(char * to_translate, t_varenv *ve)
{
	// char	**parsed;

	(void)to_translate;
	(void)ve;
	return (NULL);
}

void	clean_backslash(t_command_id *to_clean)
{
	char	*tmp;

	tmp = to_clean->value;
	to_clean->value = ft_strtrim(to_clean->value, "\\");
	free(tmp);
}

void	clean_quotes(t_command_id *to_clean, t_varenv *ve)
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
		to_clean->value = ft_strtrim(to_clean->value, "\"");
		free(tmp);
		tmp = to_clean->value;
		to_clean->value = env_transaltion_d_quotes(to_clean->value, ve);
	}
}

void	clean_section(t_list *to_clean, void *m)
{
	t_list			*cursor;
	t_command_id	*cast;
	char			**var;
	t_minishell		*minishell;

	cursor = to_clean;
	minishell = m;
	while (cursor)
	{
		cast = cursor->content;
		if (cast->id == QUOTES_S || cast->id == QUOTES_D)
			clean_quotes(cast, &(minishell->ve));
		if (cast->id == BACKSLASH)
			clean_backslash(cast);
		if (cast->id == ENV && ft_strlen(cast->value) > 1)
		{
			var = var_value_finder(&(minishell->ve), &cast->value[1], 1);
			free(cast->value);
			cast->value = ft_strdup(var[0]);
			free(var);
		}
		cursor = cursor->next;
	}
}

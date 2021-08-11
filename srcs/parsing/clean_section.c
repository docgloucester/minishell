/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:56:12 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/11 15:25:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_transaltion_d_quotes(char *to_translate, t_varenv *ve)
{
	char	**split;

	split = ft_split(to_translate, '$');
	// print_str_table(split);
	(void)ve;
	return (split[0]);
}

char	*suppress_first_char(char *to_trim)
{
	char	*ret;

	if (!to_trim)
		return (NULL);
	ret = ft_strdup(&to_trim[1]);
	return (ret);
}

void	clean_backslash(t_command_id *to_clean)
{
	char	*tmp;

	tmp = to_clean->value;
	to_clean->value = suppress_first_char(to_clean->value);
	free(tmp);
}

void	clean_quotes(t_command_id *to_clean, t_varenv *ve)
{
	char	*tmp;
	int		size;

	tmp = to_clean->value;
	size = 0;
	if (ft_strlen(to_clean->value) >= 2)
		size = ft_strlen(to_clean->value) - 2;
	if (to_clean->id == QUOTES_S)
	{
		to_clean->value = suppress_first_char(to_clean->value);
		to_clean->value[size] = 0;
		free(tmp);
	}
	if (to_clean->id == QUOTES_D)
	{
		if (size == 0)
			to_clean->value = NULL;
		else
		{
			to_clean->value = suppress_first_char(to_clean->value);
			to_clean->value[size] = 0;
		}
		free(tmp);
		/*to_clean->value = */env_transaltion_d_quotes(to_clean->value, ve);
		(void)ve;
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

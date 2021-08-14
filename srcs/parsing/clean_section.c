/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:56:12 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/12 18:22:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_d_quotes(char *to_parse)
{
	int	i;
	char	*ret;

	i = 1;
	while (to_parse[i] && (ft_isalnum(to_parse[i]) || to_parse[i] == '_') && !is_white_space(to_parse[i]))
		i++;
	ret = ft_strdup(to_parse);
	ret[i] = 0;
	return (ret);
}

char	*classic_d_quotes(char *to_parse)
{
	int	i;
	char	*ret;

	i = 0;
	while (to_parse[i] && to_parse[i] != '$')
		i++;
	ret = ft_strdup(to_parse);
	ret[i] = 0;
	return (ret); 
}

char	**split_d_quotes_env(char *to_split)
{
	int		i;
	char	**split;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	split = NULL;
	while (to_split[i])
	{
		if (to_split[i] == '$')
			str = env_d_quotes(&to_split[i]);
		else
			str = classic_d_quotes(&to_split[i]);
		split = ft_insert_str(j, split, str);
		i += ft_strlen(str); 
		j++;
	}
	return (split);
}

void	translate_d_quotes_env(char **split, t_varenv *ve)
{
	int		i;
	char	**var;
	char	*tmp;

	i = -1;
	while (split[++i])
	{
		if (split[i][0] && split[i][0] == '$' && ft_strlen(split[i]) > 1)
		{
			tmp = split[i];
			var = var_value_finder(ve, &(split[i][1]), 1);
			if (var)
				split[i] = var[0];
			else
				split[i] = NULL;
			free(tmp);
		}
	}
}

char	*join_d_quotes(char **to_join)
{
	int		i;
	char	*join;
	int		size;

	i = 1;
	size = str_table_size(to_join);
	join = to_join[0];
	while (i < size)
	{
		if (to_join[i])
			join = ft_strjoin(join, to_join[i]);
		free(to_join[i]);
		i++;
	}
	if (!join)
		return (ft_strdup(""));
	return (join);
}

char	*env_transaltion_d_quotes(char *to_translate, t_varenv *ve)
{
	char	**split;
	char	*ret;

	split = split_d_quotes_env(to_translate);
	translate_d_quotes_env(split, ve);
	ret = join_d_quotes(split);
	free(split);
	return (ret);
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
	to_clean->value = suppress_first_char(to_clean->value);
	to_clean->value[size] = 0;
	if (to_clean->id == QUOTES_D)
	{
		if (size == 0)
			to_clean->value = ft_strdup("");
		else
		{
			to_clean->value[size] = 0;
			to_clean->value = env_transaltion_d_quotes(to_clean->value, ve);
		}
	}
	(void)ve;
		free(tmp);
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
			if (var)
				cast->value = var[0];
			else
				cast->value = NULL;
		}
		cursor = cursor->next;
	}
}

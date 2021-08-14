/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:02:23 by tor               #+#    #+#             */
/*   Updated: 2021/08/08 17:40:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	classic_split(char *to_parse, char ***splited)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(to_parse);
	while (to_parse[i]
		&& ft_isascii(to_parse[i]) && !is_special_char_command(to_parse[i])
		&& !is_sep_command(to_parse[i]) && !is_white_space(to_parse[i]))
		i++;
	tmp[i] = 0;
	*splited = ft_insert_str(str_table_size(*splited), *splited, tmp);
	return (i);
}

int	special_char_split(char *to_parse, char ***splited)
{
	int		i;
	char	*tmp;

	i = 0;
	if (to_parse[i] == S_QUOTES || to_parse[i] == D_QUOTES)
		return (quotes_split(splited, to_parse));
	else if (to_parse[i] == '\\' || to_parse[i] == '$')
		return (backslash_split(to_parse, splited));
	tmp = ft_strdup(to_parse);
	while (to_parse[i])
		i++;
	tmp[i] = 0;
	return (i);
}

int	backslash_split(char *to_par, char ***splited)
{
	int		i;
	char	*tmp;
	int		is_env;

	i = 1;
	is_env = 0;
	if (to_par[0] == '$')
		is_env = 1;
	if (is_special_char_command(to_par[i]) && !is_env)
		i++;
	while (is_env && to_par[i] && (ft_isascii(to_par[i]) &&
		!(is_white_space(to_par[i]))) && !is_special_char_command(to_par[i]) && to_par[i] != D_QUOTES && to_par[i] != S_QUOTES && !is_sep_command(to_par[i]))
		i++;
	while (!is_env  && to_par[i] && (ft_isascii(to_par[i]) && !(is_white_space(to_par[i]))) && !is_special_char_command(to_par[i]))
		i++;
	tmp = ft_strdup(to_par);
	tmp[i] = 0;
	*splited = ft_insert_str(str_table_size(*splited), *splited, tmp);
	return (i);
}

int	sep_split(char *to_parse, char ***sp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (to_parse[i + 1] && to_parse[i + 1] == '>' && to_parse[i++] == '>')
	{
		*sp = ft_insert_str(str_table_size(*sp), *sp, ft_strdup(">>"));
		return (2);
	}
	if (to_parse[i + 1] && to_parse[i + 1] == '<' && to_parse[i++] == '<')
	{
		*sp = ft_insert_str(str_table_size(*sp), *sp, ft_strdup("<<"));
		return (2);
	}
	tmp = ft_strdup(to_parse);
	if (tmp[1])
		tmp[1] = 0;
	*sp = ft_insert_str(str_table_size(*sp), *sp, tmp);
	return (1);
}

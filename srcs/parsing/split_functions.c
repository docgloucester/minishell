/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:02:23 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:27:56 by nouchata         ###   ########.fr       */
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

int	backslash_split(char *to_parse, char ***splited)
{
	int		i;
	char	*tmp;

	i = 1;
	while (to_parse[i] && (ft_isascii(to_parse[i])
			&& !(is_white_space(to_parse[i]))))
		i++;
	tmp = ft_strdup(to_parse);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:21:10 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:27:52 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

char	*find_quotes(char *to_parse)
{
	int		i;
	char	*between_quotes;
	char	quotes;

	i = 0;
	quotes = to_parse[i++];
	between_quotes = ft_strdup(to_parse);
	while (to_parse[i] && to_parse[i] != quotes)
		i++;
	if (to_parse[i] && to_parse[i] == quotes)
		between_quotes[i + 1] = 0;
	return (between_quotes);
}

int	quotes_split(char ***splited, char *to_parse)
{
	char	*tmp;
	int		len;

	tmp = find_quotes(to_parse);
	*splited = ft_insert_str(str_table_size(*splited), *splited, tmp);
	len = ft_strlen(tmp);
	return (len);
}

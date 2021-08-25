/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:31:56 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/24 23:31:58 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

void	remove_char_from_str(char *str, char trm, int except_in_dbq, int x_in_q)
{
	int	i;
	int	j;
	int	dbqcount;
	int	qcount;

	i = 0;
	j = 0;
	dbqcount = 0;
	qcount = 0;
	while (str && str[i])
	{
		if (str[i - 1] != '\\' && str[i] == '\"' && qcount % 2 == 0)
			dbqcount++;
		if (str[i - 1] != '\\' && str[i] == '\'' && dbqcount % 2 == 0)
			qcount++;
		str[j] = str[i];
		i++;
		if (str[j] != trm || (except_in_dbq && dbqcount % 2 != 0)
			|| (x_in_q && qcount % 2 != 0))
			j++;
	}
	while (j <= i)
		str[j++] = 0;
}

void	strip_quotes(char *str)
{
	int	i;
	int	j;
	int	dbqcount;
	int	qcount;

	i = 0;
	j = 0;
	dbqcount = 0;
	qcount = 0;
	while (str && str[i])
	{
		if (str[i - 1] != '\\' && str[i] == '\"' && qcount % 2 == 0)
			dbqcount++;
		if (str[i - 1] != '\\' && str[i] == '\'' && dbqcount % 2 == 0)
			qcount++;
		if (qcount % 2 != 0 && str[i] == '$')
			str[j++] = '\\';
		str[j] = str[i];
		if (!((str[i] == '\'' && dbqcount % 2 == 0)
				|| (str[i] == '\"' && qcount % 2 == 0)))
			j++;
		i++;
	}
	while (j <= i)
		str[j++] = 0;
}

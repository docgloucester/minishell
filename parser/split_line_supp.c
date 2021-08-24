/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:33 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/24 14:22:27 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	error_handler(char *cmd, char *arg, int retval)
{
	write(2, "bash: ", 6);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	perror("");
	return (retval);
}

int	finished_quote_set(char *str, int i)
{
	unsigned int	dbqcount;
	unsigned int	qcount;
	int				pos;

	pos = -1;
	dbqcount = 0;
	qcount = 0;
	while (++pos < i)
	{
		if (str[pos - 1] != '\\' && str[pos] == '\'')
			qcount++;
		if (str[pos - 1] != '\\' && str[pos] == '\"')
			dbqcount++;
	}
	if (qcount % 2 == 0 && dbqcount % 2 == 0)
		return (1);
	return (0);
}

int	sep_detector(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !((str[i] == '|' || str[i] == ';')
						&& str[i - 1] != '\\'
						&& finished_quote_set(str, i)))
		i++;
	return (i + 1);
}

int	is_finished_by_pipe(t_cmdchunk *list)
{
	while (list && list->next)
		list = list->next;
	if (list->sep_type == '|')
		return (1);
	return (0);
}

t_cmdchunk *chunk_list_creator_supp(t_cmdchunk *lst)
{
	t_cmdchunk	*curr;

	if (is_finished_by_pipe(lst))
	{
		chunksdel(lst);
		return ((t_cmdchunk *)(long)error_handler(NULL, "syntax error", 0)); // a refaire
	}
	curr = lst;
	while (curr)
	{
		if (!finished_quote_set(curr->cmd, ft_strlen(curr->cmd)))
		{
			chunksdel(lst);
			return ((t_cmdchunk *)(long)error_handler(NULL, "syntax error", 0)); // a refaire
		}
		curr = curr->next;
	}
	return (lst);
}

t_cmdchunk *chunk_list_creator(char *str)
{
	int		i;
	int		y;
	t_cmdchunk *lst;
	char *cstr;

	i = 0;
	y = 0;
	lst = NULL;
	while (i < (int)ft_strlen(str))
	{
		cstr = &str[i];
		i += to_next_char(&cstr, ' ', 0);
		if (!str[i])
			break ;
		y = sep_detector(&str[i]);
		if (!chunkadd(&lst, newchunk(ft_substr(str, i, y - 1), str[i + y - 1])))
		{
			chunksdel(lst);	
			return ((t_cmdchunk *)(long)error_handler(NULL, NULL, 0));
		}
		i += y;
	}
	return (chunk_list_creator_supp(lst));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:33 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/27 10:25:42 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	unfinished_quote_set(char *s, size_t i)
{
	unsigned int	dbqcnt;
	unsigned int	qcount;
	size_t			p;

	p = 0;
	dbqcnt = 0;
	qcount = 0;
	while (s && s[p] && p < i)
	{
		if (s[p] == '\"' && (p == 0 || s[p - 1] != '\\') && qcount % 2 == 0)
			dbqcnt++;
		if (s[p] == '\'' && (p == 0 || s[p - 1] != '\\') && dbqcnt % 2 == 0)
			qcount++;
		p++;
	}
	if (qcount % 2 != 0)
		return ('\'');
	if (dbqcnt % 2 != 0)
		return ('\"');
	return (0);
}

int	sep_detector(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !((str[i] == '|' || str[i] == ';')
			&& str[i - 1] != '\\'
			&& !unfinished_quote_set(str, i)))
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

t_cmdchunk	*chunk_list_creator_supp(t_cmdchunk *lst)
{
	t_cmdchunk	*curr;
	char		c;

	if (is_finished_by_pipe(lst))
	{
		chunksdel(lst);
		return ((t_cmdchunk *)(long)error_syntax_handler("|", 1, 0));
	}
	curr = lst;
	while (curr)
	{
		c = unfinished_quote_set(curr->cmd, ft_strlen(curr->cmd));
		if (c)
		{
			chunksdel(lst);
			return ((t_cmdchunk *)(long)error_syntax_handler(&c, 1, 0));
		}
		curr = curr->next;
	}
	return (lst);
}

t_cmdchunk	*chunk_list_creator(char *str)
{
	int			i;
	int			y;
	t_cmdchunk	*lst;
	char		*cstr;

	i = 0;
	y = 0;
	lst = NULL;
	if (!str[to_next_char(&str, ' ', 0)])
		return (NULL);
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

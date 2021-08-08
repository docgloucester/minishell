/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 21:33:56 by lnoirot           #+#    #+#             */
/*   Updated: 2021/08/06 16:27:22 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

char	last_char_str(char *str)
{
	int		i;
	char	ret;

	i = -1;
	while (str[++i])
		ret = str[i];
	return (ret);
}

int	sep_error(t_list *prec, t_list *to_check)
{
	t_command_id	*cast_prec;

	cast_prec = NULL;
	if (prec)
		cast_prec = prec->content;
	if (!prec || (cast_prec && cast_prec->id == SEP) || !(to_check->next))
		return (1);
	return (0);
}

int	quotes_error(t_list *to_check)
{
	t_command_id	*cast;
	char			last;
	char			first;

	cast = to_check->content;
	first = cast->value[0];
	last = last_char_str(cast->value);
	if (first != last)
		return (1);
	return (0);
}

int	error_token(t_list *to_check)
{
	t_list			*prec;
	t_command_id	*cast;

	prec = NULL;
	while (to_check)
	{
		cast = to_check->content;
		if ((cast->id == QUOTES_D || cast->id == QUOTES_S)
			&& quotes_error(to_check))
			return (1);
		if (cast->id == SEP && sep_error(prec, to_check))
			return (1);
		prec = to_check;
		to_check = to_check->next;
	}
	return (0);
}

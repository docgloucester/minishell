/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_resolver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:15:52 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/27 11:17:53 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	get_next_var_start(char *current)
{
	int		y;
	int		z;
	char	found;

	z = 0;
	found = 1;
	while (found)
	{
		y = fchar_nesc(current, '$', z);
		if (y == -1)
			return (ft_strlen(current));
		if (!evar_name(&current[y + 1], 1))
		{
			z++;
			continue ;
		}
		if (unfinished_quote_set(current, y) != '\'')
			found = 0;
		z++;
	}
	return (y);
}

int	var_resolver_loop(char *current, char **new, t_varenv *ve)
{
	int		i;

	if (!current[get_next_var_start(current)])
		return (0);
	i = 0;
	while (current[0])
	{
		i = var_concat(current, new, ve, get_next_var_start(current));
		if (i == -1)
			return (-1);
		current = &current[i];
	}
	return (1);
}

int	var_resolver(char **cmd, t_varenv *ve)
{
	char	*new;
	int		i;

	new = NULL;
	if (!*cmd || !ft_strlen(*cmd))
		return (0);
	i = var_resolver_loop(*cmd, &new, ve);
	if (i == -1 || (new && !ft_strlen(new)))
	{
		free(new);
		new = NULL;
	}
	if (i == 1)
	{
		free(*cmd);
		*cmd = new;
	}
	return (i);
}

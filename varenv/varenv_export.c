/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:03:21 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/06 16:29:18 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

long int	envitem_len(t_envitem *ei)
{
	long int	i;
	char		**str;

	i = 0;
	i += ft_strlen(ei->name) + 1;
	i += ei->value_num;
	str = ei->value;
	while (str[0])
	{
		i += ft_strlen(str[0]);
		str = &str[1];
	}
	return (i);
}

void	fill_str(char *str, t_envitem *ei)
{
	long int	i[2];
	char		**src;

	i[0] = 0;
	i[1] = ei->value_num - 1;
	ft_strlcpy(&str[i[0]], ei->name, ft_strlen(ei->name) + 1);
	i[0] += ft_strlen(ei->name);
	str[i[0]] = '=';
	i[0]++;
	src = ei->value;
	while (src[0])
	{
		ft_strlcpy(&str[i[0]], src[0], ft_strlen(src[0]) + 1);
		i[0] += ft_strlen(src[0]);
		if (i[1] > 0)
		{
			str[i[0]] = ':';
			i[0]++;
			i[1]--;
		}
		src = &src[1];
	}
	str[i[0]] = 0;
}

char	**env_to_str(t_varenv *ve)
{
	char		**str;
	t_envitem	*ei;
	long int	i;

	ei = ve->envtab;
	i = 0;
	str = malloc(sizeof(char *) * (ve->count + 1));
	if (!str)
		return (NULL);
	while (ei)
	{
		if (!ei->value_num)
		{
			ei = ei->next;
			continue ;
		}
		str[i] = malloc(sizeof(char) * envitem_len(ei));
		if (!str[i])
			builtin_exit(ve->minishell_var);
		fill_str(str[i], ei);
		i++;
		ei = ei->next;
	}
	str[i] = NULL;
	return (str);
}

void	kill_env_to_str(char **ets)
{
	long int	i;

	i = 0;
	if (!ets)
		return ;
	while (ets[i])
	{
		free(ets[i]);
		i++;
	}
	free(ets);
}
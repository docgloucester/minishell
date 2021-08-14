/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:13:20 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/11 15:10:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

long int	value_len(char **value)
{
	long int	i;
	char		**str;

	i = 0;
	str = value;
	while (str[0])
	{
		i += ft_strlen(str[0]);
		str = &str[1];
	}
	return (i);
}

char	*value_to_str(char **value, int value_num)
{
	char		*str;
	long int	i;

	i = 0;
	if (value_num < 0)
		value_num = 0;
	str = malloc(sizeof(char) * (value_len(value) + value_num + 1));
	if (!str)
		return (NULL);
	while (value[0])
	{
		ft_strlcpy(&str[i], value[0], ft_strlen(value[0]) + 1);
		i += ft_strlen(value[0]);
		if (value_num > 0)
		{
			str[i] = ':';
			i++;
			value_num--;
		}
		value = &value[1];
	}
	str[i] = 0;
	return (str);
}

char	**str_returnval(t_varenv *ve)
{
	char		**value;

	value = malloc(sizeof(char *) * 2);
	if (!value)
		return (NULL);
	value[0] = ft_itoa(ve->bin_return);
	value[1] = NULL;
	return (value);
} 

char	**var_value_finder(t_varenv *ve, char *var_name, char malloc_str)
{
	char		**value;
	t_envitem	*ei;

	ei = ve->envtab;
	if (!ft_strncmp(var_name, "?", 0))
		return (str_returnval(ve));
	while (ei)
	{
		if (var_name && !ft_strncmp(ei->name, var_name, 0))
		{
			if (malloc_str)
			{
				value = malloc(sizeof(char *) * 2);
				if (!value)
					return (NULL);
				value[0] = value_to_str(ei->value, ei->value_num - 1);
				value[1] = NULL;
				return (value);
			}
			else
				return (ei->value);
			break ;
		}
		ei = ei->next;
	}
	return (NULL);
}

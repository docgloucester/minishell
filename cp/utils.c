/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:49:10 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:28:17 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	check_sep(int *exec_name_set)
{
	*exec_name_set = 0;
	return (SEP);
}

int	str_table_size(char **table)
{
	int	len;

	len = 0;
	if (!table)
		return (len);
	while (table[len])
		len++;
	return (len);
}

int	is_white_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v')
		return (1);
	return (0);
}

char	**ft_insert_str(int insert, char **to_realloc, char *to_insert)
{
	int		len;
	int		i;
	int		j;
	char	**tmp;

	len = str_table_size(to_realloc) + 1;
	tmp = to_realloc;
	i = 0;
	j = 0;
	to_realloc = malloc(sizeof(char *) * (len + 1));
	if (!to_realloc)
		exit(1);
	to_realloc[len] = NULL;
	if (!tmp)
		to_realloc[i++] = to_insert;
	while (i < len)
	{
		if (i == insert)
			to_realloc[i++] = to_insert;
		to_realloc[i++] = tmp[j++];
	}
	free(tmp);
	return (to_realloc);
}

void	free_str_table(char **to_free)
{
	int		i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		to_free[i] = NULL;
		i++;
	}
	free(to_free);
}

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

char	**ft_insert_str(int index, char **realloc, char *insert)
{
	int		len;
	int		i;
	int		j;
	char	**tmp;

	len = str_table_size(realloc) + 1;
	tmp = realloc;
	i = 0;
	j = 0;
	realloc = malloc(sizeof(char *) * (len + 1));
	if (!realloc)
		exit(1);
	realloc[len] = NULL;
	if (!tmp)
		realloc[i++] = insert;
	while (i < len)
	{
		if (i == index)
			realloc[i++] = insert;
		realloc[i++] = tmp[j++];
	}
	free(tmp);
	return (realloc);
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

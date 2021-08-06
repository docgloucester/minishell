/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:30:06 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:27:31 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	is_sep(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
	{
		if (c == sep[i])
			return (1);
	}
	return (0);
}

char	*word_str(char *to_split, char *sep)
{
	int		len;
	char	*word;

	len = 0;
	while (to_split[len] && !is_sep(to_split[len], sep))
		len++;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		exit(1);
	if (!word)
		return (word);
	word[len] = 0;
	while (--len >= 0)
		word[len] = to_split[len];
	return (word);
}

int	count_word(char *to_split, char *sep)
{
	int	i;
	int	word_nbr;

	i = -1;
	word_nbr = 0;
	while (to_split[++i])
	{
		if (is_sep(to_split[i], sep))
		{
			while (to_split[i] && is_sep(to_split[i], sep))
				i++;
			word_nbr++;
		}
		if (!is_sep(to_split[i], sep))
		{
			while (to_split[i] && !is_sep(to_split[i], sep))
				i++;
			word_nbr++;
		}
	}
	return (word_nbr);
}

char	**alloc_splited(char *to_split, char *sep)
{
	int		word_nbr;
	char	**splited;

	word_nbr = count_word(to_split, sep);
	splited = malloc(sizeof(char *) * word_nbr + 1);
	if (!splited)
		exit(1);
	return (splited);
}

char	**split_str(char *to_split, char *sep)
{
	char	**splited;
	int		word_nbr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_nbr = count_word(to_split, sep);
	splited = alloc_splited(to_split, sep);
	splited[word_nbr] = 0;
	if (!splited)
		return (splited);
	while (to_split[i])
	{
		if (!is_sep(to_split[i], sep))
		{
			splited[j] = word_str(&to_split[i], sep);
			while (to_split[i] && !is_sep(to_split[i], sep))
				i++;
			while (to_split[i] && is_sep(to_split[i], sep))
				i++;
			j++;
		}
	}
	return (splited);
}

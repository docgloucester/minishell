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

void	remove_char_from_str(char *str, char torem)
{
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		if (str[j] != torem)
			j++;
	}
	while (j <= i)
		str[j++] = 0;
}
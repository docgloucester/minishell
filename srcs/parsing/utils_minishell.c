/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:07:39 by tor               #+#    #+#             */
/*   Updated: 2021/08/12 18:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	is_sep_command(char c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_special_char_command(char c)
{
	if (c == '$' || c == '\\' || c == S_QUOTES || c == D_QUOTES)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:33:58 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/30 12:49:55 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int		builtin_pwd(t_execdata *d)
{
	char	buffer[1001];
	int		i;

	i = 0;
	ft_memset(buffer, 0, 1001);
	if (!getcwd(buffer, 1000))
		return (error_handler("pwd", NULL, -1));
	print_builtin(d, buffer);
	print_builtin(d, "\n");
	return (0);
}
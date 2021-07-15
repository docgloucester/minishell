/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:01:29 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 07:36:29 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"exec.h"

int	builtin_env(t_execdata *d, char **env, int (*fc)(char **))
{
	d->return_v = (*fc)(&d->cmd[1]);
	return (0);
}

int	builtin_loop(t_execdata *d, char **env);
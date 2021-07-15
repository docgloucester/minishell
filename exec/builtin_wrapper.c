/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:01:29 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/15 11:29:17 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"exec.h"

int	builtin_exec(t_execdata *d, t_varenv *ve, int (*fc)(char **))
{
	(void)ve;
	d->return_v = (*fc)(&d->cmd[1]);
	return (0);
}

int	builtin_loop(t_execdata *d, t_varenv *ve);
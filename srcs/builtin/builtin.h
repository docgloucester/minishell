/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:32:26 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/08 15:41:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTIN_H
#define BUILTIN_H

int		builtin_export(t_execdata *d, t_varenv *ve);
int		builtin_unset(t_execdata *d, t_varenv *ve);
int		builtin_envc(t_execdata *d, t_varenv *ve);
int		builtin_cd(t_execdata *d);
int		builtin_echo(t_execdata *d);
int		builtin_exit(void *minishell);
int		print_builtin(t_execdata *d, char *str);
int		builtin_dispatcher(t_execdata *d, t_varenv *ve);

#endif
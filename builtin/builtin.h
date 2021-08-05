/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:32:26 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/05 17:23:34 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTIN_H
#define BUILTIN_H

int		builtin_export(t_execdata *d, t_varenv *ve);
int		builtin_unset(t_execdata *d, t_varenv *ve);
int		builtin_envc(t_execdata *d, t_varenv *ve);
int		builtin_cd(t_execdata *d, t_varenv *ve);
int		builtin_echo(t_execdata *d, t_varenv *ve);
int		builtin_exit(void *minishell);
int		print_builtin(t_execdata *d, char *str);
int		builtin_dispatcher(t_execdata *d, t_varenv *ve);

#endif
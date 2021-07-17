/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:32:26 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 17:16:58 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTIN_H
#define BUILTIN_H

int		builtin_export(t_execdata *d, t_varenv *ve);
int		builtin_unset(t_execdata *d, t_varenv *ve);
int		builtin_envc(t_execdata *d, t_varenv *ve);
int		builtin_cd(t_execdata *d, t_varenv *ve);
int		print_builtin(t_execdata *d, char *str);
int		builtin_dispatcher(t_execdata *d, t_varenv *ve);

#endif
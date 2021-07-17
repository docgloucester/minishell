/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explorer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:40:33 by nouchata          #+#    #+#             */
/*   Updated: 2021/07/17 09:22:56 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXPLORER_H
#define EXPLORER_H
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "../minishell.h"


int		test_dir(char *path, char *cmd, int print_error);

# endif
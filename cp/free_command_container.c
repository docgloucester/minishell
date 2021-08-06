/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_container.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 12:13:07 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:27:27 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	free_command_container(t_cmd_cont *to_free)
{
	free(to_free->source_command);
	ft_lstclear(&(to_free->parsed_command), &free_command_id);
	free(to_free);
}

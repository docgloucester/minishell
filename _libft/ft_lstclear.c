/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:54:16 by nouchata          #+#    #+#             */
/*   Updated: 2019/11/10 19:13:46 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	if (*lst)
	{
		next = *lst;
		current = next;
		while (current)
		{
			next = current->next;
			del(current->content);
			free(current);
			current = next;
		}
	}
	*lst = NULL;
}

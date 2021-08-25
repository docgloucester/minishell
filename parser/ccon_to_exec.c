/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccon_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:48:20 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/25 10:48:21 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "parser.h"

char	**strtabdup(char **tab, int is_alone)
{
	char	**ret;
	int		nbstr;

	nbstr = 0;
	if (is_alone)
		nbstr = 1;
	while (!is_alone && tab[nbstr])
		nbstr++;
	ret = (char **)malloc(sizeof(char*) * (1 + nbstr));
	if (!ret)
		return (NULL);
	ret[nbstr] = NULL;
	while (--nbstr >= 0)
		ret[nbstr] = ft_strdup(tab[nbstr]);
	return (ret);
}

int	ccon_to_exec(struct s_cmdcontent *ccon)
{
	char	**cmd;

	cmd = strtabdup(ccon->cmd, 0);
	if (!cmd)
		return (-1);
	return (0);
}

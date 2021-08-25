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

int	ccon_to_exec(t_cmdcontent *ccon_full, t_minishell *m)
{
	char			**content;
	t_ioitem		*curr;
	t_exectype		binbuiltin;
	t_cmdcontent	*ccon;

	ccon = ccon_full;
	while (ccon)
	{
		curr = ccon->inputs
		while (curr)
		{
			content = strtabdup(&curr->name, 1);
			if (!content)
				return (-1);
			if (curr->type == IN)
				exec_builder(&m->ed, content, INPUT, 1);
			else
				exec_builder(&m->ed, content, DINPUT, 1);
			curr = curr->next
		}
		content = strtabdup(ccon->cmd, 0);
		if (!content)
			return (-1);
		binbuiltin = BINARY;
		if (is_builtin(content))
			binbuiltin = BUILTIN;
		if (!ccon->outputs && ccon->sep_type == ';')
			exec_builder(&m->ed, content, binbuiltin, 0);
		else
			exec_builder(&m->ed, content, binbuiltin, 1);
		curr = ccon->outputs;
		while (curr)
		{
			content = strtabdup(&curr->name, 1);
			if (!content)
				return (-1);
			if (curr->type == OUT)
				exec_builder(&m->ed, content, OUTPUT, 1);
			else
				exec_builder(&m->ed, content, DOUTPUT, 1);
			curr = curr->next
		}
		ccon = ccon->next;
	}
	return (0);
}

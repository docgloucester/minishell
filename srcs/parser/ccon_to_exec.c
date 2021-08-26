/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccon_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:48:20 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/25 16:35:59 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

char	**strtabdup(char **array, int is_alone)
{
	char	**ret;
	int		nbstr;

	nbstr = 0;
	if (is_alone)
		nbstr = 1;
	while (!is_alone && array[nbstr])
		nbstr++;
	ret = (char **)malloc(sizeof(char *) * (1 + nbstr));
	if (!ret)
		return (NULL);
	ret[nbstr] = NULL;
	while (--nbstr >= 0)
		ret[nbstr] = ft_strdup(array[nbstr]);
	return (ret);
}



int	exec_inputs(t_cmdcontent *ccon, t_minishell *m)
{
	char		**content;
	t_ioitem	*curr;

	curr = ccon->inputs;
	while (curr)
	{
		content = strtabdup(&curr->name, 1);
		if (!content)
			return (error_handler(NULL, NULL, -1));
		if (curr->type == IN)
			exec_builder(&m->ed, content, INPUT, 1);
		else
			exec_builder(&m->ed, content, INPUT_D, 1);
		curr = curr->next;
	}
	return (0);
}

int	exec_outputs(t_cmdcontent *ccon, t_minishell *m)
{
	int			is_pipe;
	char		**cnt;
	t_ioitem	*curr;

	curr = ccon->outputs;
	while (curr)
	{
		is_pipe = 1;
		if (!curr->next && ccon->sep_type == ';')
			is_pipe = 0;
		cnt = strtabdup(&curr->name, 1);
		if (!cnt)
			return (error_handler(NULL, NULL, -1));
		if (curr->type == OUT)
			exec_builder(&m->ed, cnt, OUTPUT, is_pipe);
		else
			exec_builder(&m->ed, cnt, OUTPUT_D, is_pipe);
		curr = curr->next;
	}
	return (0);
}

int	ccon_to_exec(t_cmdcontent *ccon_full, t_minishell *m)
{
	char			**content;
	t_exectype		binbuiltin;
	t_cmdcontent	*ccon;

	ccon = ccon_full;
	while (ccon)
	{
		if (exec_inputs(ccon, m) == -1)
			return (-1);
		content = strtabdup(ccon->cmd, 0);
		if (!content)
			return (error_handler(NULL, NULL, -1));
		binbuiltin = BINARY;
		if (!ccon->outputs && ccon->sep_type == ';')
			exec_builder(&m->ed, content, binbuiltin, 0);
		else
			exec_builder(&m->ed, content, binbuiltin, 1);
		if (exec_outputs(ccon, m) == -1)
			return (-1);
		ccon = ccon->next;
	}
	return (0);
}

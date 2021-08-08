/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:46:20 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:27:14 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	id_command(char *value, int *exec_name_set, char *next, t_list *last)
{
	t_command_id	*c;

	c = NULL;
	if (last)
		c = last->content;
	if (value[0] && is_sep_command(value[0]))
		return (check_sep(exec_name_set));
	if (value[0] && value[0] == '\\')
		return (BACKSLASH);
	if (value[0] && value[0] == S_QUOTES)
		return (QUOTES_S);
	if (value[0] && value[0] == D_QUOTES)
		return (QUOTES_D);
	if (value[0] && value[0] == '$')
		return (ENV);
	if (value[0] && value[0] == '-')
		return (OPTIONS);
	if (value[0] && ft_isalnum(value[0]))
		return (ARG);
	if (value[0] == ' ' && ((next && is_sep_command(next[0]))
			|| (c && (c->id == EXEC_NAME || c->id == SEP))))
		return (TO_FREE);
	else if (value[0] == ' ')
		return (END_OF_ARG);
	return (UNDEFINED);
}

void	create_lst_parsed_command(char **sp, t_cmd_cont *current_command)
{
	int				i;
	int				id;
	int				exec_name_set;
	t_list			*new;

	i = -1;
	id = 0;
	exec_name_set = 0;
	while (sp[++i])
	{
		if ((i == 0 || !exec_name_set) && sp[i][0] && ft_isalnum(sp[i][0]))
		{
			id = EXEC_NAME;
			exec_name_set = 1;
		}
		else
			id = id_command(sp[i], &exec_name_set, sp[i + 1],
					ft_lstlast(current_command->parsed_command));
		if (id != TO_FREE)
			new = command_id_create(sp[i], id);
		if (!current_command->parsed_command && id != TO_FREE)
			current_command->parsed_command = new;
		else if (id != TO_FREE)
			ft_lstadd_back(&(current_command->parsed_command), new);
	}
}

char	**split_command(char *s_cmd)
{
	char	**sp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s_cmd);
	sp = NULL;
	while (i < len)
	{
		if (!is_white_space(s_cmd[i]) && is_special_char_command(s_cmd[i]))
			i += special_char_split(&s_cmd[i], &sp);
		else if (ft_isascii(s_cmd[i]) && !is_sep_command(s_cmd[i])
			&& !is_special_char_command(s_cmd[i])
			&& s_cmd[i] != 0
			&& !is_white_space(s_cmd[i]))
			i += classic_split(&s_cmd[i], &sp);
		else if (!is_white_space(s_cmd[i]) && is_sep_command(s_cmd[i]))
			i += sep_split(&s_cmd[i], &sp);
		if (is_white_space(s_cmd[i]))
			sp = ft_insert_str(str_table_size(sp), sp, ft_strdup(" "));
		while (i < len && is_white_space(s_cmd[i]))
			i++;
	}
	return (sp);
}

void	current_command_process(t_cmd_cont *current_command)
{
	char	**splited_command;

	splited_command = split_command(current_command->source_command);
	create_lst_parsed_command(splited_command, current_command);
	free_str_table(splited_command);
}

t_cmd_cont	*command_parsing(char *command_line)
{
	t_cmd_cont		*current_command;

	current_command = malloc(sizeof(t_cmd_cont));
	if (!current_command)
		exit(1);
	current_command->parsed_command = NULL;
	current_command->source_command = ft_strdup(command_line);
	current_command_process(current_command);
	return (current_command);
}

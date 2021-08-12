/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct_debug.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:18:06 by tor               #+#    #+#             */
/*   Updated: 2021/08/12 11:47:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	print_command_container(t_cmd_cont *to_print)
{
	t_list			*cursor;
	t_command_id	*cast;

	printf(">%s\n", to_print->source_command);
	cursor = to_print->parsed_command;
	while (cursor)
	{
		cast = cursor->content;
		printf(">>>%d\t%s\n", cast->id, cast->value);
		cursor = cursor->next;
	}
}

void	print_conmmand_id_lst(t_list *to_print)
{
	t_list			*cursor;
	t_command_id	*cast;

	cursor = to_print;
	printf("Lst : \n");
	while (cursor)
	{
		cast = cursor->content;
		printf(">%d\t%s\n", cast->id, cast->value);
		cursor = cursor->next;
	}
}

// void	print_proc_command_lst(t_list *to_print)
// {
// 	t_list			*cursor;
// 	t_proc_command	*cast;
// 	int				i;

// 	cursor = to_print;
// 	while (cursor)
// 	{
// 		cast = cursor->content;
// 		printf("TR: \tcmd\n");
// 		i = -1;
// 		while (cast->cmd[++i])
// 			printf("\t%s\n", cast->cmd[i]);
// 		printf("type : %d\tpipe: %d\n", cast->type, cast->pipe);
// 		cursor = cursor->next;
// 	}
// }

void	print_proc_cmd_lst(t_list *to_print)
{
	t_proc_command	*cast;

	printf("TRANSLATED\n");
	if (!to_print)
		printf("EMPTYYYY!!!\n");
	while (to_print)
	{
	printf("====NODE====\n");
		cast = to_print->content;
		printf("\tPIPE : %d\tKIND : %d\nStr\n", cast->pipe, cast->type);
		print_str_table(cast->cmd);
			print_conmmand_id_lst(cast->subsection);
		to_print = to_print->next;
	}
}

void	print_str_table(char **to_print)
{
	int	i;

	i = -1;
	if (!to_print)
		printf("This is an empty table\n");
	else
	{
		while (to_print[++i])
			printf("!%s!\n", to_print[i]);
	}
}

void debug_execdata(t_execdata * data)
{
	printf("===== EXECDATA =====\n");
	while (data)
	{
		printf("++ NODE ++\n");
		print_conmmand_id_lst(data->stocked_list);
		printf("type : %d\n", data->type);
		print_str_table(data->cmd);
		printf("pipe_on : %d\n", data->pipe_on);
		data = data->next;
	}
} 


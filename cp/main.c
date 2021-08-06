/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:05:46 by tor               #+#    #+#             */
/*   Updated: 2021/08/06 16:33:37 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

void	xxxxx(t_list *to_print)
{
	t_list			*cursor;
	t_list			*tmp;
	t_command_id	*cast;

	cursor = to_print;
	//printf("Lst : \n");
	while (cursor)
	{
		cast = cursor->content;
		//printf(">%d\t%s\n", cast->id, cast->value);
		if (cast->value)
			free(cast->value);
		free(cast);
		tmp = cursor;
		cursor = cursor->next;
		free(tmp);
	}
}

void	print_proc_cmd_lst(t_list *to_print)
{
	t_proc_command	*cast;
	t_list			*tmp;

	//printf("TRANSLATED\n");
	while (to_print)
	{
		cast = to_print->content;
		//printf("\tPIPE : %d\tKIND : %d\nStr\n", cast->pipe, cast->type);
		//print_str_table(cast->cmd);
		//print_conmmand_id_lst(cast->subsection);
		tmp = to_print;
		to_print = to_print->next;
		free_str_table(cast->cmd);
		xxxxx(cast->subsection);
		free(cast);
		free(tmp);
	}
}

void	free_command_id(void *to_free)
{
	t_command_id	*cast;

	cast = to_free;
	free(cast->value);
	cast->value = NULL;
}

void	free_subsection(t_list *subsection)
{
	ft_lstclear(&subsection, &free_command_id);
}

void	free_proc_cmd(void *to_clean)
{
	t_proc_command	*cast;

	cast = to_clean;
	free_str_table(cast->cmd);
	free_subsection(cast->subsection);
	free(to_clean);

}

void	free_proc_cmd_lst(t_list *translated)
{
	// t_proc_command *cast;
	// t_list *ls;

	// ls = translated;
	// cast = ls->content;
	// while (ls)
	// {
	// 	printf("%s", cast->cmd[0]);
	// 	ls = ls->next;
	// 	cast = ls->content;
	// }
	ft_lstclear(&translated, &free_proc_cmd);
}

void	free_pp(t_list **list)
{
	int	i;

	i = -1;
	while (list[++i])
	{
		xxxxx(list[i]);
	}
}

int     main(int ac, char **av)
{
    int                     i;
    t_cmd_cont     *parsed;
	t_list			**tmp;
	t_list			*translated;

    i = 1;
    if (ac < 2)
        return (0);
    if (av[i])
    {
		if (ft_strlen(av[i]))
		{
        	parsed = command_parsing(av[i]);
			tmp = process_parsed_command(parsed);
			translated = translate_cmd(tmp);
			exec_cleaner(&translated);
			printf("---%s\n", parsed->source_command);
			// t_list *x = parsed->parsed_command;
			// t_command_id *ci;
			// while (x)
			// {
			// 	ci = x->content;
			// 	printf("%s ", ci->value);
			// 	x = x->next;
			// }
			// printf("\n");
			free(parsed->source_command);
			// free_command_container(parsed);
			ft_lstclear(&(parsed->parsed_command), &free_command_id);
			free(parsed);
			free_proc_cmd_lst(translated);
			free_pp(tmp);
			free(tmp);
			// print_proc_cmd_lst(translated);
			// free_cmd_lst(&translated);
		}
    }
}
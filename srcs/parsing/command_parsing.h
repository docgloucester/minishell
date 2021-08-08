/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:13:13 by tor               #+#    #+#             */
/*   Updated: 2021/08/08 15:57:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_PARSING_H
# define COMMAND_PARSING_H
# define S_QUOTES 39
# define D_QUOTES 34
# include "../minishell.h"

typedef enum e_parsed_id
{
	UNDEFINED,
	EXEC_NAME,
	OPTIONS,
	ARG,
	SEP,
	QUOTES_S,
	QUOTES_D,
	BACKSLASH,
	ENV,
	END_OF_ARG,
	TO_FREE
}							t_parsed_id;

typedef struct s_command_id
{
	char					*value;
	char					id;
}							t_command_id;

typedef struct s_command_container
{
	char					*source_command;
	t_list					*parsed_command;
}							t_cmd_cont;

typedef struct s_processed_command
{
	t_list			*subsection;
	char			**cmd;
	int				type;
	int				pipe;
}					t_proc_command;

char			**split_str(char *to_split, char *sep);
t_cmd_cont		*command_parsing(char *command_line);
int				str_table_size(char **table);
char			**ft_insert_str(int index, char **realloc, char *insert);
int				is_white_space(char c);
int				quotes_split(char ***splited, char *to_parse);
int				classic_split(char *to_parse, char ***splited);
int				special_char_split(char *to_parse, char ***splited);
int				backslash_split(char *to_parse, char ***splited);
int				sep_split(char *to_parse, char ***splited);
int				env_split(char *to_parse, char ***splited);
char			*find_quotes(char *to_parse);
int				is_sep_command(char c);
int				is_special_char_command(char c);
void			free_str_table(char **to_free);
int				lst_size(t_list *to_count);
// void			free_command_container(t_cmd_cont *to_free);
t_list			*command_id_create(char *value, int id);
void			free_command_id(void *to_free);

void			print_command_container(t_cmd_cont *to_print);
void			print_conmmand_id_lst(t_list *to_print);
void			print_proc_command_lst(t_list *to_print);
void			print_proc_command_lst(t_list *to_print);
void			print_str_table(char **to_print);

t_list			**process_parsed_command(t_cmd_cont *command_parsed);
int				count_sep_lst(t_list *to_count);
t_proc_command	*proc_command_create(char **cmd, int type, int pipe);
t_list			**split_lst(t_list *to_split);
int				is_pipe(t_command_id *to_check);
int				set_pipe(t_list **to_proc);
int				is_semi_colon(t_command_id *t);
void			erase_last_commad_id_lst(t_list *lst);
int				is_command_id_value_sep(t_command_id *t);
void			exec_parsed_command(t_cmd_cont *command_parsed);
int				set_type_parsing(t_list *last);

int				error_token(t_list *to_check);
t_list			*translate_cmd(t_list **to_translate);
void			print_proc_cmd_lst(t_list *to_print);
int				is_pipe(t_command_id *to_check);
int				check_sep(int *exec_name_set);

void			malloc_protected(void *to_alloc, size_t size);
void			clean_backslash(t_command_id *to_clean);
void			clean_quotes(t_command_id *to_clean);
void			clean_section(t_list **to_clean, void *m);
void			exec_cleaner(void *m, t_list **to_clean);

char			**create_cmd(t_list *to_translate);
void			free_translate(t_list *to_free);
void			go_to_sep(t_list **to_translate);
void			create_cmd_lst(t_list **lst, t_list *to_trans);
t_proc_command	*create_proc_command(t_list *to_translate);

#endif

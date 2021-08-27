/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:10:46 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/27 11:05:36 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

enum {din, in, dout, out};

typedef struct s_cmdchunk
{
	char				*cmd;
	char				sep_type;
	struct s_cmdchunk	*next;
	struct s_cmdchunk	*prev;
}				t_cmdchunk;

typedef struct s_chunkseg
{
	char				**segments;
	char				sep_type;
	char				segs_count;
	struct s_chunkseg	*next;
	struct s_chunkseg	*prev;
}				t_chunkseg;

typedef struct s_ioitem
{
	char				type;
	char				*name;
	struct s_ioitem		*next;
	struct s_ioitem		*prev;
}				t_ioitem;

typedef struct s_cmdcontent
{
	struct s_ioitem		*inputs;
	struct s_ioitem		*outputs;
	char				**cmd;
	char				sep_type;
	struct s_cmdcontent	*next;
	struct s_cmdcontent	*prev;
}				t_cmdcontent;

/* ******** MISC */

long		fchar_nesc(char *src, char c, int already_find);
int			remove_spaces(char **src, int just_surround_spaces);
int			to_next_char(char **src, char c, int edit_str);
int			find_next_sep(char *src);
void		remove_char_from_str(char *s, char trm, int ex_in_dbq, int x_in_q);
void		strip_quotes(char *str);
char		**strtabdup(char **array, int is_alone);
int			unfinished_quote_set(char *s, size_t i);

/* ******** CHUNKSEG */

int			find_size_of_current_block(char *src);
int			count_all_segments(char *src);
char		**extract_segments(char *src);
char		**kill_segments(char **segs, int count);
int			count_strs(char **strs, int count);
int			chunkseg_builder(t_chunkseg **cs, t_cmdchunk *cmdc);
int			chunkseg_killer(t_chunkseg *cs);

/* ******** CMDCONTENT */

int			cmdcontent_builder(t_cmdcontent **ccon, t_chunkseg *cs);
void		cmdcontent_killer(t_cmdcontent *ccon);
int			ioitem_builder(t_cmdcontent *curr, char *str, char *content);
int			cmdcontent_extract_iothings(t_cmdcontent *ccon, t_chunkseg *cs);
int			cmdcontent_extract_cmd(t_cmdcontent *ccon, t_chunkseg *cs);

/* ******** CMDCHUNK */

t_cmdchunk	*chunk_list_creator(char *str);
t_cmdchunk	*newchunk(char *str, char sep);
int			chunkadd(t_cmdchunk **chunklist, t_cmdchunk *new);
void		chunksdel(t_cmdchunk *list_to_del);

/* ******** SECOND PARSER (FOR QUOTES AND STUFF) */

int			is_builtin(char **cmd);
void		remove_nullspaces(char **arr, int cmdcount);
void		strip_quotes(char *str);
void		remove_char_from_str(char *str, char trm, \
			int xpt_in_dbq, int x_in_q);
int			get_next_var_start(char *current);
char		*evar_name(char *str, int just_count);

#endif
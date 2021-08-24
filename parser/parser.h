/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:10:46 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 18:00:23 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../_libft/libft.h"

enum {DIN, IN, DOUT, OUT};

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
	int					sep_type;
	char				segs_count;
	struct s_chunkseg	*next;
	struct s_chunkseg	*prev;
}				t_chunkseg;

typedef struct s_ioinfo
{
	char				type;
	char				*name;
	struct s_ioinfo		*next;
	struct s_ioinfo		*prev;
}				t_ioinfo;

typedef struct s_cmdcontent
{
	struct s_ioinfo		*inputs;
	struct s_ioinfo		*outputs;
	char				**cmd;
	struct s_cmdcontent	*next;
	struct s_cmdcontent	*prev;
}				t_cmdcontent;

/*struct	s_heuristics
{
//	char					*to_export;
	char					*prog;
	char					**args;
	char					*input_path;
	char					*output_path;
	int						is_passing_output;
	struct	s_heuristics	*next;
	struct	s_heuristics	*previous;
}		t_heuristics;
*/


long		fchar_nesc(char *src, char c, int already_find);
int			remove_spaces(char **src, int just_surround_spaces);
int			to_next_char(char **src, char c, int edit_str);
int			find_next_sep(char *src);
int			find_size_of_current_block(char *src);
int			count_all_segments(char *src);
char		**extract_segments(char *src);
char		**kill_segments(char **segs);
int			count_strs(char **strs);
int			chunkseg_builder(t_chunkseg **cs, t_cmdchunk *cmdc);
int			chunkseg_killer(t_chunkseg *cs);

t_cmdchunk *chunk_list_creator(char *str);

t_cmdchunk	*newchunk(char *str, char sep);
int	chunkadd(t_cmdchunk **chunklist, t_cmdchunk *new);
void	chunksdel(t_cmdchunk *list_to_del);

# endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:10:46 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/24 14:21:49 by nouchata         ###   ########.fr       */
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

enum {PIPE, SEMICO};

typedef struct s_cmdchunk
{
	char				*cmd;
	int					sep_type;
	struct s_cmdchunk	*next;
	struct s_cmdchunk	*prev;
	
}				t_cmdchunk;

typedef struct s_chunkseg
{
	char				**segments;
	int					sep_type;
	struct s_chunkseg	*next;
	struct s_chunkseg	*prev;
}				t_chunkseg;

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

t_cmdchunk	*split_line(char *line);

t_cmdchunk	*newchunk(char *str, int sep);
int	chunkadd(t_cmdchunk **chunklist, t_cmdchunk *new);
t_cmdchunk	*split_line(char *line);

# endif
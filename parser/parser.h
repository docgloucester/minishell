/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:10:46 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/23 17:33:47 by nouchata         ###   ########.fr       */
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



long		find_char_not_escaped(char *src, char c, int already_find);
int			remove_spaces(char **src, int just_surround_spaces);
char		*to_next_char(char *src, char c);
int			find_next_sep(char *src);
int			count_all_sep(char *src);

t_cmdchunk	*split_line(char *line);

t_cmdchunk	*newchunk(char *str, int sep);
int	chunkadd(t_cmdchunk **chunklist, t_cmdchunk *new);
t_cmdchunk	*split_line(char *line);

# endif
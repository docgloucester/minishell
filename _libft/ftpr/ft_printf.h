/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:53:19 by nouchata          #+#    #+#             */
/*   Updated: 2021/03/18 12:51:18 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_flags {
	unsigned int	f_size;
	int				l_align;
	int				z_fill;
	int				is_prec;
	unsigned int	prec;
}				t_flags;

int				ft_printf(const char *stnce, ...);
void			pr_mirrorswap(char *src);
unsigned int	pr_strlen(const char *src);
unsigned int	pr_printchar(const char *src, int len);
char			*pr_calloc(size_t size, char filling);
t_flags			pr_create_flags(void);
int				pr_get_prec(t_flags *flags, const char *str, va_list ap);
int				pr_get_field(t_flags *flags, const char *str, va_list ap);
t_flags			pr_get_flags(const char *str, va_list ap);
char			*pr_field_handler(char *src, t_flags f);
void			pr_zero_handler(char *src);
char			*pr_num_prec_handler(char *src, t_flags f);
char			*pr_neg_prec_handler(char *src, t_flags f);
char			*pr_make_char(char c, t_flags f);
char			*pr_make_str(char *str, t_flags f);
unsigned int	pr_ptr_len(long int ptr);
char			*pr_make_hexnum(long int dec, char alphabet);
char			*pr_make_xint(unsigned int dec, t_flags f, int maj);
unsigned int	pr_num_len(long int num);
char			*pr_itoa(long int src);
char			*pr_make_int(int num, t_flags f);
char			*pr_make_uint(unsigned int num, t_flags f);
char			*pr_make_ptr(void *ptr, t_flags f);
char			*pr_null_pointer(t_flags f);
int				pr_conversion_spec(const char *str);
char			*pr_make_arg(char c, t_flags f, va_list ap);
int				pr_parsing(const char *str, va_list ap, int *p_char);

#	endif

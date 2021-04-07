# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 11:57:19 by nouchata          #+#    #+#              #
#    Updated: 2021/03/18 14:27:21 by nouchata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./ft_memset.c \
			./ft_bzero.c \
			./ft_memcpy.c \
			./ft_memccpy.c \
			./ft_memmove.c \
			./ft_memchr.c \
			./ft_memcmp.c \
			./ft_strlen.c \
			./ft_strlcpy.c \
			./ft_strlcat.c \
			./ft_strchr.c \
			./ft_strrchr.c \
			./ft_strnstr.c \
			./ft_strncmp.c \
			./ft_atoi.c \
			./ft_isalpha.c \
			./ft_isdigit.c \
			./ft_isalnum.c \
			./ft_isascii.c \
			./ft_isprint.c \
			./ft_toupper.c \
			./ft_tolower.c \
			./ft_calloc.c \
			./ft_strdup.c \
			./ft_substr.c \
			./ft_strjoin.c \
			./ft_strtrim.c \
			./ft_split.c \
			./ft_itoa.c \
			./ft_strmapi.c \
			./ft_putchar_fd.c \
			./ft_putstr_fd.c \
			./ft_putendl_fd.c \
			./ft_putnbr_fd.c \
			./ft_lstnew.c \
			./ft_lstadd_front.c \
			./ft_lstsize.c \
			./ft_lstlast.c \
			./ft_lstadd_back.c \
			./ft_lstdelone.c \
			./ft_lstclear.c \
			./ft_lstiter.c \
			./gnl.c \
			./gnl_utils.c \

PR_SRCS	=	./ftpr/ft_printf.c \
			./ftpr/ft_printf_utils.c \
			./ftpr/ft_hex_relatives.c \
			./ftpr/ft_num_relatives.c \
			./ftpr/ft_parsing_relatives.c \
			./ftpr/ft_pointer_relatives.c \
			./ftpr/ft_char_relatives.c \
			./ftpr/ft_flags_parser.c \
			./ftpr/ft_flags_relatives.c

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

OBJS	=	${SRCS:.c=.o}

OBJS_PR	=	${PR_SRCS:.c=.o}

NAME	=	libft.a

RM		=	rm -f

.c.o:
			${CC} -I. ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_PR}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

printf:		${OBJS} ${OBJS_PR}
			ar rc ${NAME} ${OBJS} ${OBJS_PR}
			ranlib ${NAME}

.PHONY:		all clean fclean re bonus

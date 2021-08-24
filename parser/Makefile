# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 14:30:50 by nouchata          #+#    #+#              #
#    Updated: 2021/08/23 14:36:19 by nouchata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = $(wildcard *.c)
CC = clang
FLAGS = -Wall -Werror -Wextra -g3
OBJS = ${FILES:.c=.o}
NAME = parser

.c.o:
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			@${CC} ${FLAGS} -o ${NAME} ${OBJS} ../_libft/libft.a -lreadline
			@echo "DONE"

clean:
			@rm -Rf ${OBJS}
			@echo "CLEANED"

fclean:		clean
			@rm -Rf ${NAME}
			@echo "FCLEANED"

re:			fclean all
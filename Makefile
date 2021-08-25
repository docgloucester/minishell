# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 10:06:20 by nouchata          #+#    #+#              #
#    Updated: 2021/08/25 14:45:10 by nouchata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CTN =		srcs
SRCS_E =	${CTN}/exec/bin_wrapper.c \
			${CTN}/exec/builtin_wrapper.c \
			${CTN}/exec/exec_builder.c \
			${CTN}/exec/exec_main.c \
			${CTN}/exec/export_wrapper.c \
			${CTN}/exec/import_wrapper.c \
			${CTN}/exec/misc_wrapper.c
SRCS_V = 	${CTN}/varenv/varenv_construct.c \
			${CTN}/varenv/varenv_export.c \
			${CTN}/varenv/varenv_finder.c \
			${CTN}/varenv/varenv_utils_supp.c \
			${CTN}/varenv/varenv_utils.c
SRCS_B =	${CTN}/builtin/builtin.c \
			${CTN}/builtin/builtin_cd.c \
			${CTN}/builtin/builtin_export.c \
			${CTN}/builtin/builtin_export_misc.c \
			${CTN}/builtin/builtin_echo.c \
			${CTN}/builtin/builtin_exit.c \
			${CTN}/builtin/builtin_var.c
SRCS_P =	${CTN}/parser/parser.c \
			${CTN}/parser/remove_spaces.c \
			${CTN}/parser/split_line_supp.c \
			${CTN}/parser/chunk_handling.c \
			${CTN}/parser/chunkseg_builder.c \
			${CTN}/parser/chunkseg_misc.c \
			${CTN}/parser/cmdcontent_builder.c \
			${CTN}/parser/cmdcontent_misc.c \
			${CTN}/parser/misc.c \
			${CTN}/parser/quotes_management.c
SRCS_M =	${CTN}/main.c ${CTN}/error_handler.c
OBJS_E =	${SRCS_E:.c=.o}
OBJS_V =	${SRCS_V:.c=.o}
OBJS_M =	${SRCS_M:.c=.o}
OBJS_B =	${SRCS_B:.c=.o}
OBJS_P =	${SRCS_P:.c=.o}
LIB_E =		${CTN}/exec/exec.a
LIB_V =		${CTN}/varenv/varenv.a
LIB_B =		${CTN}/builtin/builtin.a
LIB_P =		${CTN}/parser/parser.a
CC =		clang
CFLAGS =	-g #-Wall -Werror -Wextra
NAME =		minishell
RM =		rm -f

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

libft:
			@cd _libft && ${MAKE}
			@echo "✓ Libft"

varenv:		libft ${OBJS_V}
			@ar rc ${LIB_V} ${OBJS_V}
			@ranlib ${LIB_V}
			@echo "✓ Env container"

exec:		libft varenv ${OBJS_E}
			@ar rc ${LIB_E} ${OBJS_E}
			@ranlib ${LIB_E}
			@echo "✓ Exec container"

builtin:	libft ${OBJS_B}
			@ar rc ${LIB_B} ${OBJS_B}
			@ranlib ${LIB_B}
			@echo "✓ Built-in container"

parser:		libft ${OBJS_P}
			@ar rc ${LIB_P} ${OBJS_P}
			@ranlib ${LIB_P}
			@echo "✓ Parser container"

${NAME}:	libft varenv builtin exec parser ${OBJS_M}
			@${CC} ${CFLAGS} ${OBJS_M} -o ${NAME} \
			${LIB_P} ${LIB_E} ${LIB_B} ${LIB_V} _libft/libft.a -lreadline
			@echo "✨✨ minishell is compiled ! ✨✨"

clean:
			@${RM} ${OBJS_V}
			@${RM} ${OBJS_E}
			@${RM} ${OBJS_M}
			@${RM} ${OBJS_B}
			@${RM} ${OBJS_P}
			@cd _libft && ${MAKE} clean
			@echo "✨✨ .o cleaned ✨✨"

fclean:		clean
			@${RM} ${LIB_V}
			@${RM} ${LIB_E}
			@${RM} ${LIB_B}
			@${RM} ${LIB_P}
			@${RM} ${NAME}
			@cd _libft && ${MAKE} fclean
			@echo "✨✨ all cleaned ✨✨"

re:			fclean all

.PHONY:		all clean fclean varenv exec builtin libft re
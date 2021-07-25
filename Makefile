# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 10:06:20 by nouchata          #+#    #+#              #
#    Updated: 2021/07/25 13:41:14 by nouchata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_E =	exec/bin_wrapper.c \
			exec/builtin_wrapper.c \
			exec/exec_builder.c \
			exec/exec_main.c \
			exec/export_wrapper.c \
			exec/import_wrapper.c \
			exec/misc_wrapper.c
SRCS_V = 	varenv/varenv_construct.c \
			varenv/varenv_export.c \
			varenv/varenv_finder.c \
			varenv/varenv_utils_supp.c \
			varenv/varenv_utils.c
SRCS_B =	builtin/builtin.c \
			builtin/builtin_cd.c \
			builtin/builtin_export.c \
			builtin/builtin_echo.c \
			builtin/builtin_exit.c \
			builtin/builtin_var.c
SRCS_M =	main.c error_handler.c
OBJS_E =	${SRCS_E:.c=.o}
OBJS_V =	${SRCS_V:.c=.o}
OBJS_M =	${SRCS_M:.c=.o}
OBJS_B =	${SRCS_B:.c=.o}
CC =		gcc
CFLAGS =	#-Wall -Werror -Wextra
NAME =		minishell
RM =		rm -f

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

libft:
			@cd _libft && ${MAKE}
			@echo "✓ Libft"

varenv:		libft ${OBJS_V}
			@ar rc varenv/varenv.a ${OBJS_V}
			@ranlib varenv/varenv.a
			@echo "✓ Env container"

exec:		libft varenv ${OBJS_E}
			@ar rc exec/exec.a ${OBJS_E}
			@ranlib exec/exec.a
			@echo "✓ Exec container"

builtin:	libft ${OBJS_B}
			@ar rc builtin/builtin.a ${OBJS_B}
			@ranlib builtin/builtin.a
			@echo "✓ Built-in container"		

${NAME}:	libft varenv builtin exec ${OBJS_M}
			@${CC} ${CFLAGS} ${OBJS_M} -o ${NAME} exec/exec.a \
			varenv/varenv.a _libft/libft.a builtin/builtin.a
			@echo "✨✨ minishell is compiled ! ✨✨"

clean:
			@${RM} ${OBJS_V}
			@${RM} ${OBJS_E}
			@${RM} ${OBJS_M}
			@${RM} ${OBJS_B}
			@cd _libft && ${MAKE} clean
			@echo "✨✨ .o cleaned ✨✨"

fclean:		clean
			@${RM} varenv/varenv.a
			@${RM} exec/exec.a
			@${RM} builtin/builtin.a
			@${RM} ${NAME}
			@cd _libft && ${MAKE} fclean
			@echo "✨✨ all cleaned ✨✨"

re:			fclean all

.PHONY:		all clean fclean varenv exec builtin libft re
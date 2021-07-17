# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 10:06:20 by nouchata          #+#    #+#              #
#    Updated: 2021/07/17 09:19:26 by nouchata         ###   ########.fr        #
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
			varenv/varenv_utils.c \
			varenv/varenv.c
SRCS_F = 	explorer/check_dir.c
SRCS_M =	main.c error_handler.c
OBJS_E =	${SRCS_E:.c=.o}
OBJS_V =	${SRCS_V:.c=.o}
OBJS_M =	${SRCS_M:.c=.o}
OBJS_F = 	${SRCS_F:.c=.o}
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

explorer:	libft ${OBJS_F}
			@ar rc explorer/explorer.a ${OBJS_F}
			@ranlib explorer/explorer.a
			@echo "✓ Explorer lib"

${NAME}:	libft varenv exec explorer ${OBJS_M}
			@${CC} ${CFLAGS} ${OBJS_M} -o ${NAME} exec/exec.a \
			varenv/varenv.a explorer/explorer.a _libft/libft.a
			@echo "✨✨ minishell is compiled ! ✨✨"

clean:
			@${RM} ${OBJS_V}
			@${RM} ${OBJS_E}
			@${RM} ${OBJS_M}
			@cd _libft && ${MAKE} clean
			@echo "✨✨ .o cleaned ✨✨"

fclean:		clean
			@${RM} varenv/varenv.a
			@${RM} exec/exec.a
			@${RM} ${NAME}
			@cd _libft && ${MAKE} fclean
			@echo "✨✨ all cleaned ✨✨"

re:			fclean all

.PHONY:		all clean fclean varenv exec libft re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvinstudent.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 10:06:20 by nouchata          #+#    #+#              #
#    Updated: 2021/08/08 13:19:56 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

CC	=		gcc
CFLAGS	=	-Wall -Werror -Wextra -MMD -g3
NAME	=		minishell
RM	=		rm -rf

SRCS_PATH = srcs

SRCS_E_PATH	=	exec/
SRCS_V_PATH	=	varenv/
SRCS_B_PATH	=	builtin/
SRCS_P_PATH	=	parsing/

OBJ_PATH = ./obj/

LIBS = -lreadline

LIBFT_PATH	=	_libft
LIBFT_MAKE	= $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB	=	-L$(LIBFT_PATH) -lft

SRCS_E_LIST	=	$(addprefix $(SRCS_E_PATH), \
					bin_wrapper.c \
					builtin_wrapper.c \
					exec_builder.c \
					exec_main.c \
					export_wrapper.c \
					import_wrapper.c \
					misc_wrapper.c \
				)
SRCS_V_LIST	=	$(addprefix $(SRCS_V_PATH), \
					varenv_construct.c \
					varenv_export.c \
					varenv_finder.c \
					varenv_utils_supp.c \
					varenv_utils.c \
				)
SRCS_B_LIST	=	$(addprefix $(SRCS_B_PATH), \
					builtin.c \
					builtin_cd.c \
					builtin_export.c \
					builtin_echo.c \
					builtin_exit.c \
					builtin_var.c \
				)
SRCS_P_LIST	=	$(addprefix $(SRCS_P_PATH), \
					clean_section.c \
					command_parsing.c \
					create_cmd.c \
					error_parsing.c \
					exec_cleaner.c \
					ft_split_str.c \
					process_parsed_command_utils.c \
					process_parsed_command.c \
					quotes_split_utils.c \
					split_functions.c \
					struct_command_id.c \
					translate_utils.c \
					translate.c \
					utils_lst.c \
					utils_minishell.c \
					utils_struct_debug.c \
					utils.c \
					free_lst.c\
					create_cmd_lst.c \
				)
SRCS_M_LIST	=		main.c \
					error_handler.c

SRCS	=	$(SRCS_E_LIST) \
			$(SRCS_P_LIST) \
			$(SRCS_M_LIST) \
			$(SRCS_V_LIST) \
			$(SRCS_B_LIST)

OBJS	=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
					$(CC) $(CFLAGS) -c $< -o $@


DEPS	=	$(OBJS:.o=.d)

all:		libft
			@mkdir -p obj/exec obj/builtin obj/parsing obj/explorer obj/varenv
			$(MAKE) ${NAME}
			@echo "✓ Builtin"
			@echo "✓ Parsing"
			@echo "✓ Explorer"
			@echo "✓ Varenv"

libft:
			$(LIBFT_MAKE)
			@echo "✓ Libft"

${NAME}:	$(OBJS)
			$(CC) $(OBJS) $(LIBS) $(LIBFT_LIB) -o $(NAME)
			@echo "✨✨ minishell is compiled ! ✨✨"

clean:
			$(RM) $(OBJS)
			$(LIBFT_MAKE) clean
			$(RM) $(DEPS)
			@echo "✨✨ .o cleaned ✨✨"

fclean:		clean
			$(LIBFT_MAKE) fclean
			$(RM) $(NAME)
			$(RM) $(OBJ_PATH)
			$(RM) $(DEPS)
			@echo "✨✨ all cleaned ✨✨"

run:		$(NAME)
			./minishell

vg:			$(NAME)
			valgrind --track-origins=yes ./minishell

re:			fclean all

readline:	
			sudo apt update && sudo apt install libreadline-dev

.PHONY:		all clean fclean libft re rn vg readline

-include $(DEPS)
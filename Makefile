OBJS_DIR		=	.objs
SRCS_DIR		=	src
BUILTINS_DIR	=	$(SRCS_DIR)/builtins
ERRORS_DIR		=	$(SRCS_DIR)/errors
PARSING_DIR		=	$(SRCS_DIR)/parsing
SIGNALS_DIR		=	$(SRCS_DIR)/signals
INITIALISATION_DIR	=	$(SRCS_DIR)/initialisation
UTILS_DIR	=	$(SRCS_DIR)/utils
HEADER_DIR		=	includes

PRINTF_PATH		=	./ft_printf
PRINTF			=	${PRINTF_PATH}/libftprintf.a

LIB				=	$(HEADER_DIR)/minishell.h

SRC			=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/init.c \
				$(SRCS_DIR)/execution/exec_command.c \
				$(SRCS_DIR)/execution/ft_split_modified.c \
				$(SRCS_DIR)/execution/utils.c \
				$(SRCS_DIR)/execution/error.c \
				$(SRCS_DIR)/execution/execution.c \
				$(SRCS_DIR)/execution/redirection.c \
				$(SRCS_DIR)/execution/pipe.c \
				$(SRCS_DIR)/execution/here_docs.c \
				$(SRCS_DIR)/env/env_management.c \
				$(SRCS_DIR)/env/env_management_utils.c \
				$(BUILTINS_DIR)/echo.c \
				$(BUILTINS_DIR)/pwd.c \
				$(BUILTINS_DIR)/cd.c \
				$(BUILTINS_DIR)/env.c \
				$(BUILTINS_DIR)/exit.c \
				$(BUILTINS_DIR)/export.c \
				$(BUILTINS_DIR)/export_print_env.c \
				$(BUILTINS_DIR)/unset.c \
				$(BUILTINS_DIR)/error_unset_export.c \
				$(ERRORS_DIR)/format_handling.c \
				$(ERRORS_DIR)/format_handling_utils.c \
				$(ERRORS_DIR)/malloc_error.c \
				$(PARSING_DIR)/parser.c \
				$(PARSING_DIR)/file_checker.c \
				$(PARSING_DIR)/file_checker_utils.c \
				$(PARSING_DIR)/delete_spaces.c \
				$(PARSING_DIR)/delete_spaces_utils.c \
				$(PARSING_DIR)/extract_command.c \
				$(PARSING_DIR)/tokenize_input.c \
				$(PARSING_DIR)/create_command_array.c \
				$(PARSING_DIR)/create_command_array_utils.c \
				$(PARSING_DIR)/clean_command_array.c \
				$(PARSING_DIR)/clean_command_array_utils.c \
				$(PARSING_DIR)/replace_variable.c \
				$(PARSING_DIR)/replace_variable_utils.c \
				$(PARSING_DIR)/replace_variable_utils2.c \
				$(PARSING_DIR)/replace_variable_utils3.c \
				$(PARSING_DIR)/replace_variable_utils4.c \
				$(PARSING_DIR)/replace_variable_utils5.c \
				$(PARSING_DIR)/parser_utils.c \
				$(PARSING_DIR)/double_rafters.c \
				$(PARSING_DIR)/check_for_heredoc.c \
				$(PARSING_DIR)/special_vars.c \
				$(PARSING_DIR)/special_vars_utils.c \
				$(PARSING_DIR)/replace_tilde.c \
				$(SIGNALS_DIR)/signals.c \
				$(SIGNALS_DIR)/signals_child.c \
				$(INITIALISATION_DIR)/initialisation.c \
				$(INITIALISATION_DIR)/initialisation_utils.c \
				$(UTILS_DIR)/ft_strdup_minishell.c \
				$(UTILS_DIR)/ft_strjoin_minishell.c \

OBJ			=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

NAME	=	minishell

CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -g3 -I $(HEADER_DIR) -I $(PRINTF_PATH)


all:	lib $(NAME)

$(NAME):	$(OBJ) $(LIB)
			$(CC) $(OBJ) $(FLAGS) -l readline $(PRINTF) -o $(NAME)

$(OBJS_DIR)/%.o:		$(SRCS_DIR)/%.c $(LIB) $(PRINTF)
			mkdir -p $(@D)
			$(CC) $(FLAGS) -c $< -o $@

lib:
		make -C $(PRINTF_PATH)

clean:
		make clean -C $(PRINTF_PATH)
		rm -f ${OBJ}
		rm -f ${NAME}

fclean:	clean
		make fclean -C $(PRINTF_PATH)
		rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re

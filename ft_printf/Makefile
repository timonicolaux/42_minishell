OBJS_DIR	=	.objs
SRCS_DIR	=	src
HEADER_DIR	=	includes

LIBFT_PATH	=	./libft
LIBFT	=	${LIBFT_PATH}/libft.a

LIB	=	$(HEADER_DIR)/ft_printf.h

SRC =	$(SRCS_DIR)/ft_printf.c \
		$(SRCS_DIR)/print_char.c \
		$(SRCS_DIR)/print_str.c \
		$(SRCS_DIR)/print_num.c \
		$(SRCS_DIR)/print_unsigned.c \
		$(SRCS_DIR)/print_hex.c \
		$(SRCS_DIR)/print_pointer.c

OBJ  = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Wextra -Werror -I $(HEADER_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(LIB)
				 mkdir -p $(@D)
				 $(CC) $(FLAGS) -c $< -o $@

all: lib $(NAME)

lib:
		make -C $(LIBFT_PATH)

$(NAME):	$(OBJ) $(LIB) $(LIBFT)
			cd ${LIBFT_PATH} && cp libft.a ../${NAME}
			ar rcs $(NAME) $(OBJ)
			ranlib $(NAME)

clean:
	make clean -C ${LIBFT_PATH}
	rm -f libftprintf.a
	rm -f ${OBJ}

fclean: clean
	make fclean -C ${LIBFT_PATH}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

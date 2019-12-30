# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 12:25:19 by sghezn            #+#    #+#              #
#    Updated: 2019/12/30 04:04:49 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME := libftprintf.a

SRC := ft_printf.c num_utils.c print_int.c print.c specification_1.c specification_2.c
OBJ := $(SRC:%.c=%.o)

INC := ft_printf.h
LIB := libft/libft.h

CC := gcc
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft
	@cp ./libft/libft.a $(NAME)
	$(CC) $(CFLAGS) -c $(SRC) -I $(INC) -I $(LIB)
	@ar rc $(NAME) $(OBJ)

clean:
	@make -C libft clean
	/bin/rm -rf $(OBJ)

fclean: clean
	@make -C libft fclean
	/bin/rm -rf $(NAME)

re: fclean all

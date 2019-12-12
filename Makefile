# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 12:25:19 by sghezn            #+#    #+#              #
#    Updated: 2019/12/12 18:29:18 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAG = -Wall -Wextra -Werror
SRC = ft_printf.c numeric.c print_int.c print.c specification_1.c specification_2.c
OBJ = ft_printf.o numeric.o print_int.o print.o specification_1.o specification_2.o

all: $(NAME)

$(NAME): lib $(OBJ)
	gcc $(FLAG) -o $(NAME) $(OBJ) -L libft -lft

$(OBJ):
	gcc $(FLAG) -c $(SRC) -I ft_printf.h -I libft/libft.h

lib:
	make -C libft

clean:
	make -C libft clean
	/bin/rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)

re: fclean all

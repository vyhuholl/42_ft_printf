# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 12:25:19 by sghezn            #+#    #+#              #
#    Updated: 2019/10/02 15:59:24 by sghezn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAG = -Wall -Wextra -Werror
SRC = auxillary.c ft_printf.c specification.c
OBJ = auxillary.o ft_printf.o specification.o

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

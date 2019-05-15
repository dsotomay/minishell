# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/24 16:20:33 by dysotoma          #+#    #+#              #
#    Updated: 2018/09/24 16:20:38 by dysotoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -g -Wall -Wextra -Werror

SRC = built_in.c built_in2.c main.c parsing.c minishell.c

OBJ = $(patsubst %.c, %.o, $(SRC))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	@gcc $(FLAGS) $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT): libft/*.c
	make -C libft/

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft/

re: fclean all
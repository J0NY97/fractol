# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/06 13:02:49 by jsalmi            #+#    #+#              #
#    Updated: 2020/10/01 14:35:43 by jsalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRCS = ./main.c\
		./input.c\
		./calculate.c\
		./init.c\
		./mouse_input.c\
		./error.c\
		./help.c\
		./color.c\
		./fractol_calculation.c
OBJS = ./*.o
LIBS = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror
MINI = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -lpthread -o $(NAME) $(FLAGS) -I ./minilibx $(SRCS) $(LIBS) -L ./minilibx $(MINI)

clean:
	make clean -C ./libft
	/bin/rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean

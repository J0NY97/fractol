# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/06 13:02:49 by jsalmi            #+#    #+#              #
#    Updated: 2020/08/06 13:02:50 by jsalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRCS = ./main.c
OBJS = ./*.o
LIBS = ./libft/libft.a
MINI = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
		gcc -o $(NAME) -I ./minilibx $(SRCS) $(LIBS) -L ./minilibx $(MINI)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
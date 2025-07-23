# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 12:04:54 by aaleixo-          #+#    #+#              #
#    Updated: 2025/07/23 17:37:03 by fragarc2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SOURCES = \
	srcs/main.c srcs/utils/utils.c srcs/utils/utils2.c srcs/parsing/parsing.c \
	srcs/parsing/parsing_help.c srcs/parsing/parsing_help2.c srcs/graphics/raycast.c
OBJECTS = $(SOURCES:.c=.o)
MAKE_LIBFT = make -C ./lib/libft
MAKE_MINILIBX = make -C ./lib/minilibx-linux

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./lib/minilibx-linux
ADLIBS = ./lib/libft/libft.a
MLX_FLAGS = -L./lib/minilibx-linux -lmlx -lX11 -lXext -lm

all: $(NAME)

$(ADLIBS):
	$(MAKE_MINILIBX)
	$(MAKE_LIBFT)

$(NAME): $(OBJECTS) $(ADLIBS)
	$(CC) $(CFLAGS) $(OBJECTS) $(ADLIBS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJECTS)
	$(MAKE_MINILIBX) clean
	$(MAKE_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re

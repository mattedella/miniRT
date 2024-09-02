# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 14:10:57 by mdella-r          #+#    #+#              #
#    Updated: 2024/09/02 17:04:51 by mdella-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	miniRT.c utilsRT.c initMiniRT.c my_malloc.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		window_utils/utils.c \
		param_object/geom_object.c param_object/option_object.c param_object/checker_range.c \
		Render/render.c  Render/render_sphere.c Render/render_cylinder.c Render/render_plane.c Render/render_light.c Render/render_utils.c\
		vector_operator/vector.c vector_operator/vector2.c 

NAME = miniRT

LIBFT_DIR = libft/
LIBFT = libft/libft.a
MLX_DIR = Minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

COMPILE = gcc -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all: $(MLX_DIR) $(NAME)

$(MLX_DIR):
		@git clone $(MLX_REPO) $(MLX_DIR)
		@cd $(MLX_DIR) && ./configure


$(NAME): $(OBJS)
		@make -C $(LIBFT_DIR)
		@$(COMPILE) $(OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx_Linux -I$(MLX_DIR) -lXext -lX11 -lm -o $(NAME)
		@echo compiled $(NAME)

%.o: %.c
		$(COMPILE) -I . -c $< -o $@ 

clean:
		rm -f $(OBJS) $(BOBJS)
		@make clean -C $(LIBFT_DIR)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)

re: fclean all
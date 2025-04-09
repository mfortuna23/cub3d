# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 10:41:53 by mfortuna          #+#    #+#              #
#    Updated: 2025/03/12 11:14:54 by mfortuna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.INCLUDEDIRS	: /src /libft

OS 				:= $(shell uname)
CC				= cc
CFLAGS 			= -Wall -Werror -Wextra -g
#CFLAGS 			+= -fsanitize=address
RM				= rm -rf
NAME			= cub3D
LIBFT_PATH		= $(INCLUDES)libft/
NAMELIB			= $(INCLUDES)libft/libft.a
INCLUDES		= includes/
SRC_M			= src/
GAME			= $(addprefix $(SRC_M)game/, init.c game.c pixel.c render.c player_vision.c \
					player_move.c player_aux.c vision_aux.c)
UTILS			= $(addprefix $(SRC_M)utils/, cleaner.c utils.c)
MAP_V			= $(addprefix $(SRC_M)map_val/, map_checker.c map_checker_aux.c map_file.c \
					textures.c p_player.c)
SRC				= $(SRC_M)main.c $(UTILS) $(MAP_V) $(GAME)
ODIR			= obj
OBJS			= $(patsubst $(SRC_M)%.c,$(ODIR)/%.o,$(SRC))

#BONUS
B_NAME			= cub3D_bonus
B_DIR			= src_bonus/
B_GAME			= $(addprefix $(B_DIR)game_bonus/, init_bonus.c game_bonus.c pixel_bonus.c \
				render_bonus.c player_vision_bonus.c player_move_bonus.c player_aux_bonus.c \
				vision_aux_bonus.c) 
B_UTILS			= $(addprefix $(B_DIR)utils_bonus/, cleaner_bonus.c utils_bonus.c)
B_MAP_V			= $(addprefix $(B_DIR)map_val_bonus/, map_checker_bonus.c map_checker_aux_bonus.c \
					map_file_bonus.c textures_bonus.c p_player_bonus.c)
B_SRC			= $(B_DIR)main_bonus.c $(B_UTILS) $(B_MAP_V) $(B_GAME)
B_OBJS			= $(patsubst $(B_DIR)%.c,$(B_ODIR)/%.o,$(B_SRC))
B_ODIR			= obj_bonus

#MLX
MLX_DIR			= mlx/
MAKE			= make -C
ifeq ($(OS), Linux)
	MLX_FLAGS	= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
	MLX_LIB		= $(MLX_DIR)libmlx_Linux.a
	MLX_TGZ		= minilibx-linux.tgz
else
	MLX_FLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLX_LIB 	= $(MLX_DIR)libmlx.a
	MLX_TGZ		= minilibx_opengl.tgz
endif


all: $(NAME) 

bonus : $(B_NAME)

$(NAME) : $(MLX_LIB)  $(OBJS) $(NAMELIB)
	@echo "🔧 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) $(NAMELIB) $(MLX_LIB) -lm -o $(NAME)
	@echo "✅ $(NAME) ready!"

$(B_NAME) : $(MLX_LIB)  $(B_OBJS) $(NAMELIB)
	@echo "🔧 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(B_OBJS) $(NAMELIB) $(MLX_LIB) -lm -o $(B_NAME)
	@echo "✅ $(B_NAME) ready!"

$(NAMELIB) : $(LIBFT_PATH)
	@echo "Creating $(NAMELIB)..."
	@$(MAKE) $(LIBFT_PATH) > /dev/null 2>&1
	@echo "✅ Done!"

$(MLX_LIB) : $(MLX_DIR)
	@echo "creating $(MLX_LIB)..."
	@$(MAKE) $(MLX_DIR) > /dev/null 2>&1
	@echo "✅ Done!"

$(MLX_DIR): $(MLX_TGZ)
	@echo "Creating mlx folder..."
	@mkdir -p $(MLX_DIR)
	@echo "Unpacking $(MLX_TGZ) to mlx..."
	@tar -xzf $(MLX_TGZ) -C $(MLX_DIR) --strip-components=1
	@echo "✅ Done!"

$(ODIR):
	@mkdir -p $(ODIR)
	
$(ODIR)/%.o: $(SRC_M)%.c | $(B_ODIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(B_ODIR):
	@mkdir -p $(B_ODIR)
	
$(B_ODIR)/%.o: $(B_DIR)%.c | $(B_ODIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@${RM} ${ODIR}
	@${RM} ${B_ODIR}
	@$(MAKE) $(LIBFT_PATH) clean > /dev/null 2>&1

fclean: clean
	@echo "🧹 Cleaning up..."
	@$(RM) $(NAME)
	@$(RM) $(B_NAME)
	@$(RM) $(MLX_DIR)
	@$(RM) $(NAMELIB)
	@echo "✅ Clean complete!"

re: fclean all
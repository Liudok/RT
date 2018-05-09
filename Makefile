# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 12:28:37 by ftymchyn          #+#    #+#              #
#    Updated: 2018/05/07 17:14:34 by skamoza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = RT
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g

SRCS_DIR    = ./src
OBJS_DIR    = ./obj
HEADERS_DIR = ./include
LIBFT_DIR   = ./libft
LIBJSON_DIR = ./libJSON

HEADERS     = rt.h panels.h tinyfiledialogs.h cl_wrap.h parser.h kernel.h
HEADERS    := $(addprefix $(HEADERS_DIR)/, $(HEADERS))

SRCS        = main.c sdl_init.c buttons.c file_for_rendering.c panel.c validation.c \
              new_scene.c parsing.c parser_utils.c create.c tinyfiledialogs.c \
              primitive.c camera.c cross.c dot.c normalize.c vadd.c vlen.c \
              vrotate.c vsub.c create_rotation_matrix.c cl_wrapper.c \
              save_to_json.c saving_utils.c save_to_png.c sdl_utils.c get_prims_details.c \
              handling_window_resizable.c is_camera_event.c is_quit.c vmul.c\
              is_window_resizable.c off_event.c on_event.c rotate_camera.c new_prim.c new_prim2.c add_new_figure.c \
              update_camera.c init_opencl.c modify_scene.c settings_win.c check_pressing.c \
              change_value.c setting_win_textures.c real_setting_win_textures.c after_effects.c \

OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I include/
INCLUDES   += -I libft/
INCLUDES   += -I frameworks/SDL2.framework/Headers/
INCLUDES   += -I frameworks/SDL2_image.framework/SDL2_image/Headers
INCLUDES   += -I /Library/Frameworks/SDL2.framework/Versions/Current/Headers

LIBFT       = $(LIBFT_DIR)/libft.a
LIBJSON     = $(LIBJSON_DIR)/libJSON.a

LIBRARIES   = -lm -lpthread -framework OpenCL
LIBRARIES  += -L libft/ -lft -framework AppKit
LIBRARIES  += -L libJSON/ -lJSON
LIBRARIES  += -F frameworks/
LIBRARIES  += -framework SDL2 -framework SDL2_image -framework SDL2_ttf

TO_LINKING  = $(addprefix $(OBJS_DIR)/, $(OBJS)) $(INCLUDES) $(LIBRARIES) -rpath frameworks/

VPATH       = $(SRCS_DIR) $(OBJS_DIR) $(SRCS_DIR)/opencl $(SRCS_DIR)/scene $(SRCS_DIR)/math
VPATH      += $(SRCS_DIR)/gui $(SRCS_DIR)/parsing $(SRCS_DIR)/icons $(SRCS_DIR)/events

all         : $(NAME)

$(NAME)     : $(LIBFT) $(LIBJSON) $(OBJS_DIR) $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(NAME) $(TO_LINKING)
	@printf "\e[38;5;46m./$(NAME)   SUCCESSFUL BUILD 🖥\e[0m\n"

$(LIBFT)    :
	@make -C $(LIBFT_DIR)

$(LIBJSON)  :
	@make -C $(LIBJSON_DIR)

$(OBJS_DIR) :
	@mkdir $(OBJS_DIR)
	@printf "\e[38;5;46m$(OBJS_DIR)    FOLDER CREATED\e[0m\n"

$(OBJS)     : %.o : %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $(OBJS_DIR)/$@ $(INCLUDES)

clean       :
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(LIBJSON_DIR) clean
	@printf "\e[38;5;226m$(OBJS_DIR)    FOLDER DELETED\e[0m\n"

fclean      : clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LIBJSON_DIR) fclean
	@printf "\e[38;5;226m./$(NAME)   DELETED\e[0m\n"

re          : fclean all

.PHONY: clean fclean re

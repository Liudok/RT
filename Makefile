# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 12:28:37 by ftymchyn          #+#    #+#              #
#    Updated: 2018/04/25 09:14:26 by lberezyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = demo
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -O3

SRCS_DIR    = ./src
OBJS_DIR    = ./obj
HEADERS_DIR = ./include

HEADERS     = rt.h panels.h tinyfiledialogs.h cl_wrap.h parser.h kernel.h
HEADERS    := $(addprefix $(HEADERS_DIR)/, $(HEADERS))

SRCS        = main.c sdl_init.c buttons.c file_for_rendering.c panel.c sdl_utils.c new_scene.c \
              parsing.c parser_utils.c create.c tinyfiledialogs.c primitive.c camera.c \
              cross.c dot.c normalize.c vadd.c vlen.c vmul.c vrotate.c vsub.c createRotationMatrix.c \
              cl_wrapper.c init_opencl.c save_to_json.c saving_utils.c save_to_png.c\
              handlingWindowResizable.c isCameraEvent.c isQuit.c isWindowResizable.c \
              offEvent.c onEvent.c rotateCamera.c updateCamera.c 

OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I include/
INCLUDES   += -I libft/
INCLUDES   += -I /frameworks/SDL2_image.framework/SDL2_image/Headers
INCLUDES   += -I /frameworks/SDL2_ttf.framework/Headers
INCLUDES   += -I /Library/Frameworks/SDL2.framework/Versions/Current/Headers

LIBRARIES   = -lm -lpthread -framework OpenCL
LIBRARIES  += -L libft/ -lft -framework AppKit
LIBRARIES  += -L libJSON/ -lJSON
LIBRARIES  += -F frameworks/
LIBRARIES  += -framework SDL2
LIBRARIES  += -framework SDL2_image
LIBRARIES  += -framework SDL2_ttf

TO_LINKING  = $(addprefix $(OBJS_DIR)/, $(OBJS)) $(INCLUDES) $(LIBRARIES) -rpath frameworks/

VPATH       = $(SRCS_DIR) $(OBJS_DIR) $(SRCS_DIR)/opencl $(SRCS_DIR)/scene $(SRCS_DIR)/math
VPATH      += $(SRCS_DIR)/gui $(SRCS_DIR)/parsing $(SRCS_DIR)/icons $(SRCS_DIR)/events

all         : $(NAME)

$(NAME)     : $(OBJS_DIR) $(OBJS) $(HEADERS)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(TO_LINKING)
	@printf "\e[38;5;46m./$(NAME)   SUCCESSFUL BUILD 🖥\e[0m\n"

$(OBJS_DIR) :
	@mkdir $(OBJS_DIR)
	@printf "\e[38;5;46m$(OBJS_DIR)    FOLDER CREATED\e[0m\n"

$(OBJS)     : %.o : %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $(OBJS_DIR)/$@ $(INCLUDES)

clean       :
	@rm -rf $(OBJS_DIR)
	@printf "\e[38;5;226m$(OBJS_DIR)    FOLDER DELETED\e[0m\n"

fclean      : clean
	@rm -f $(NAME)
	@printf "\e[38;5;226m./$(NAME)   DELETED\e[0m\n"

re          : fclean all

.PHONY: clean fclean re

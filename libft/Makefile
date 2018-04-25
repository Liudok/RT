#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/10 09:24:49 by lberezyn          #+#    #+#              #
#    Updated: 2017/08/10 12:58:22 by lberezyn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME  	= libft.a
CC    	= clang
CFLAGS	=-Wall -Wextra -Werror

SRC   	= ft_putchar.c ft_putstr.c ft_putnbr.c ft_strlen.c ft_strdup.c ft_strcmp.c \
		ft_strcpy.c ft_strncpy.c ft_atoi.c ft_bzero.c \
		ft_memset.c ft_memcpy.c ft_memccpy.c ft_memalloc.c ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_memdel.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcat.c \
		ft_strncat.c ft_strcat.c ft_strstr.c ft_strnstr.c ft_striter.c ft_strclr.c \
		ft_strdel.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
		ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_strnew.c ft_itoa.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c \
		ft_toupper.c ft_putchar_fd.c ft_putendl.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		ft_lstmap.c ft_sqrt.c ft_swapi.c ft_swap_str.c ft_sorti.c ft_revstr.c get_next_line.c \
		ft_lstpushback.c

OFILES   = $(SRC:.c=.o)

all      : $(NAME)

$(NAME)  : $(OFILES) libft.h
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME) 

$(OFILES) : %.o : %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean     :
	@rm -f *.o

fclean    : clean
	@rm -f $(NAME)

re: fclean all

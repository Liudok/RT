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

NAME = libft.a

SRC = ft_putchar.c ft_putstr.c ft_putnbr.c ft_strlen.c ft_strdup.c ft_strcmp.c \
ft_strcpy.c ft_strncpy.c ft_atoi.c ft_bzero.c \
ft_memset.c ft_memcpy.c ft_memccpy.c ft_memalloc.c ft_memmove.c ft_memchr.c \
ft_memcmp.c ft_memdel.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcat.c \
ft_strncat.c ft_strcat.c ft_strstr.c ft_strnstr.c ft_striter.c ft_strclr.c \
ft_strdel.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_strnew.c ft_itoa.c \
ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c \
ft_toupper.c ft_putchar_fd.c ft_putendl.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
ft_lstmap.c ft_sqrt.c ft_swapi.c ft_swap_str.c ft_sorti.c ft_revstr.c get_next_line.c ft_lstpushback.c

OFILES = ft_putchar.o ft_putstr.o ft_putnbr.o ft_strlen.o ft_strdup.o \
ft_strcmp.o ft_strcpy.o ft_strncpy.o ft_atoi.o \
ft_bzero.o ft_memset.o ft_memcpy.o ft_memccpy.o ft_memalloc.o ft_memmove.o \
ft_memchr.o ft_memcmp.o ft_memdel.o ft_strchr.o ft_strrchr.o ft_strncmp.o \
ft_strlcat.o ft_strncat.o ft_strcat.o ft_strstr.o ft_strnstr.o ft_striter.o \
ft_strclr.o ft_strdel.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o \
ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_strnew.o \
ft_itoa.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
ft_tolower.o ft_toupper.o ft_putchar_fd.o ft_putendl.o ft_putstr_fd.o \
ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o \
ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_sqrt.o ft_swapi.o ft_swap_str.o \
ft_sorti.o ft_revstr.o get_next_line.o ft_lstpushback.o

all: $(NAME)

$(OFILES): $(SRC) libft.h
	@gcc -Wall -Werror -Wextra -c $(SRC)

$(NAME): $(OFILES) libft.h
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME) 

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

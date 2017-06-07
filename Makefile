# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/02 19:09:44 by qdegraev          #+#    #+#              #
#    Updated: 2017/06/07 10:30:32 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft_malloc_$(HOSTTYPE).so

HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

FLAGS= -Wall -Wextra -Werror
CC= clang
INCLUDES= includes/
LIBPATH= libft
LIB= $(LIBPATH)/libft.a

VPATH= srcs/
SRCS= \
	  malloc.c \
	  free.c \
	  realloc.c \
	  show_alloc_mem.c \
	  zone_tools.c

OBJDIR= objs/
OBJS= $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

default: all

test: $(NAME)
	$(CC) $(FLAGS) -I $(INCLUDES) -I libft/include/ -L libft -lft -L . -lft_malloc -o test test.c

all: $(LIB) $(NAME)

$(LIB):
	make -C $(LIBPATH)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) -L $(LIBPATH) -lft
	ln -s $(NAME) libft_malloc.so

$(OBJDIR)%.o: %.c
	$(CC) $(FLAGS) -I libft/include -I $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) libft_malloc.so

re: fclean all

.PHONY: re clean fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/02 19:09:44 by qdegraev          #+#    #+#              #
#    Updated: 2017/06/02 19:54:31 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft_malloc_$(HOSTTYPE).so

HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

FLAGS= -Wall -Wextra -Werror
CC= clang
INCLUDES= includes/

VPATH= srcs/
SRCS= \
	  malloc.c \
	  free.c \
	  realloc.c \
	  show_alloc_mem.c

OBJDIR= objs/
OBJS= $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

test: $(NAME)
	$(CC) $(FLAGS) -I $(INCLUDES) -L . -lft_malloc -o test test.c

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	ln -s $(NAME) libft_malloc.so

$(OBJDIR)%.o: %.c
	$(CC) $(FLAGS) -I $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) libft_malloc.so

re: fclean all

.PHONY: re clean fclean all

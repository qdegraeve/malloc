# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/02 19:09:44 by qdegraev          #+#    #+#              #
#    Updated: 2017/06/09 20:01:27 by qdegraev         ###   ########.fr        #
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
	  calloc.c \
	  free.c \
	  realloc.c \
	  show_alloc_mem.c \
	  zone_tools.c \
	  debug.c \
	  norme.c

OBJDIR= objs/
OBJS= $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

default: all

test: re
	$(CC) $(FLAGS) -I $(INCLUDES) -lpthead -L. -lft_malloc -o test tests/test.c

all: $(LIB) $(NAME)

$(LIB):
	make -C $(LIBPATH)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) -L $(LIBPATH) -lft
	ln -sf $(NAME) libft_malloc.so

$(OBJDIR)%.o: %.c $(OBJDIR)
	$(CC) $(FLAGS) -I libft/include -I $(INCLUDES) -o $@ -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	make clean -C $(LIBPATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -rf $(NAME) libft_malloc.so

re: fclean all

.PHONY: re clean fclean all

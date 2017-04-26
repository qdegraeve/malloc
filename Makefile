# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 16:28:10 by qdegraev          #+#    #+#              #
#    Updated: 2017/04/26 11:06:59 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang
FLAGS=-Wall -Wextra -Werror
NAME=
NAMES= Colleen Grace Sully
SRC= $(addsuffix .c, $(NAMES))
OBJ= $(SRC:.c=.o)
TO_CLEAN=

all: $(NAMES)

$(NAMES):
	$(MAKE) $@.o
	$(CC) $@.o  -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(SRC)

re: fclean all

.phony: re clean fclean


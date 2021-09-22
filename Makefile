# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:23:48 by ikhadem           #+#    #+#              #
#    Updated: 2021/09/22 11:27:38 by ikhadem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := server
CLIENT := client

SRC :=	server.c \
		client.c \

OBJ := $(SRC:.c=.o)

CC = gcc
# FLAG = -Wall -Wextra -Werror
HDR = minitalk.h
INCLUDE = -I.

%.o : %.c $(HDR)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAG) $(INCLUDE) server.o -o $(NAME)
	$(CC) $(FLAG) $(INCLUDE) client.o -o $(CLIENT)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(CLIENT)

re : fclean all

bonus: re

.PHONY : all clean fclean re
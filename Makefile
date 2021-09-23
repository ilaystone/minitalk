# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/21 10:23:48 by ikhadem           #+#    #+#              #
#    Updated: 2021/09/23 13:23:53 by ikhadem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		=	\e[38;5;118m
L_BLUE		=	\e[96m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(L_BLUE)INFO$(RESET)]

NAME	:=
SERVER	:= server
CLIENT	:= client

SERVER_SRC :=	server.c \

CLIENT_SRC :=	client.c \

SERVER_OBJ := $(SERVER_SRC:.c=.o)

CLIENT_OBJ := $(CLIENT_SRC:.c=.o)

CC = gcc
FLAG = -Wall -Wextra -Werror
HDR = minitalk.h
LIB = -L./ft_utils/ -lutils
INCLUDE = -I. -I./t_stack/ -I./ft_utils/

%.o : %.c $(HDR)
	@$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

all: $(SERVER) $(CLIENT)

$(NAME) : all

$(SERVER) : $(SERVER_OBJ)
	@make -C ./ft_utils/
	@$(CC) $(FLAG) $(INCLUDE) $(LIB) $(SERVER_OBJ) -o $(SERVER)
	@printf "$(_SUCCESS) $(SERVER) is ready!.\n"

$(CLIENT) : $(CLIENT_OBJ)
	@$(CC) $(FLAG) $(INCLUDE) $(LIB) $(CLIENT_OBJ) -o $(CLIENT)
	@printf "$(_SUCCESS) $(CLIENT) is ready!.\n"


clean :
	@make clean -C ./ft_utils/
	@rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	@printf "$(_SUCCESS) $(SERVER)_objects removed!.\n"
	@printf "$(_SUCCESS) $(CLIENT)_objects removed!.\n"

fclean : clean
	@make fclean -C ./ft_utils/
	@rm -f $(SERVER) $(CLIENT)
	@printf "$(_SUCCESS) $(SERVER)_exec removed!.\n"
	@printf "$(_SUCCESS) $(CLIENT)_exec removed!.\n"

re : fclean all

bonus: $(SERVER) $(CLIENT)

.PHONY : all clean fclean re bonus
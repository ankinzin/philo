# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 15:17:05 by ankinzin          #+#    #+#              #
#    Updated: 2023/09/04 12:46:37 by ankinzin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Compiler & flags //////////////////////////////////////////////////////////////
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 #-fsanitize=thread
THREAD = -pthread

# Source Files /////////////////////////////////////////////////////////////////
SRCDIR = ./src/
SRC = activity.c spare.c spare2.c check.c initialization.c \
		main.c utilities.c utilities2.c
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJ		= $(addprefix $(SRCDIR), $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(THREAD) $(OBJ) -o $(NAME)
	@echo "\033[1;33m🍝 Compilation \033[1;32mSUCCESS! 🎉\033[0m"

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

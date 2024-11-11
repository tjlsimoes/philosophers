# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:52:49 by tjorge-l          #+#    #+#              #
#    Updated: 2024/11/11 09:56:54 by tjorge-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := philo

CC := cc

CFLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS = -g

SRC := server.c

OBJ := $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ)

fclean: clean
	$(RM) $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

re: fclean all

.PHONY: all philo clean fclean debug re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 09:52:49 by tjorge-l          #+#    #+#              #
#    Updated: 2024/11/20 10:25:47 by tjorge-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := philo

CC := cc

CFLAGS := -pthread -Wall -Wextra -Werror
DEBUG_FLAGS = -fsanitize=address -g

SRC := main.c error.c \
init_a.c init_b.c init_c.c \
routine_a.c routine_b.c routine_c.c

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

.PHONY: all clean fclean debug re

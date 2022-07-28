# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 23:38:54 by sielee            #+#    #+#              #
#    Updated: 2022/07/29 00:23:28 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = philo_bonus

INC_DIR = inc
SRCS_DIR = philo/srcs

SRCS = $(addsuffix _bonus.c,$(addprefix $(B_SRCS_DIR)/,\
		main))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(FLAGS) -I $(INC_DIR) -c $^ -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re

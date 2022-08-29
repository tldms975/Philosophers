# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 23:38:54 by sielee            #+#    #+#              #
#    Updated: 2022/08/29 16:07:52 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = philo_bonus

SRCS = $(addsuffix _bonus.c,\
		ft_atoui\
		ft_strlen\
		ft_malloc\
		ft_error\
		ft_free\
		init\
		routine\
		monitoring\
		simulate\
		time\
		print_state\
		terminate\
		main)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(FLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re

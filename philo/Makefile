# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 23:38:54 by sielee            #+#    #+#              #
#    Updated: 2022/08/31 22:40:02 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread

NAME = philo

SRCS = $(addsuffix .c,\
		ft_atoui\
		ft_strlen\
		ft_malloc\
		ft_error\
		ft_free\
		init\
		routine\
		routine_fork\
		monitoring\
		simulate\
		time\
		print_state\
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

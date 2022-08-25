# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 23:38:54 by sielee            #+#    #+#              #
#    Updated: 2022/08/25 15:48:15 by sielee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = philo

INC_DIR = inc
SRCS_DIR = srcs

SRCS = $(addsuffix .c,$(addprefix $(SRCS_DIR)/,\
		ft_atoui\
		ft_strlen\
		ft_malloc\
		ft_error\
		ft_free\
		ft_init\
		ft_routine\
		time\
		print_state\
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

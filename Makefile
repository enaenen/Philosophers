# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wchae <wchae@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 16:16:12 by wchae             #+#    #+#              #
#    Updated: 2022/05/11 20:04:37 by wchae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
AR		= ar rcs
RM		= rm -f
LEAK	= -g3 -fsanitize=address

SRC = main.c parse.c philo_run.c
SRCS = $(addprefix $(SRCS_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -o $@ -c $?

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:		fclean all

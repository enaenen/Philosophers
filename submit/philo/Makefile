# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wchae <wchae@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 16:16:12 by wchae             #+#    #+#              #
#    Updated: 2022/05/24 22:17:48 by wchae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
AR		= ar rcs
RM		= rm -f
LEAK	= -g3 -fsanitize=thread
TEMP    =

SRC = main.c parse.c philo_run.c routine.c time_util.c
SRCS = $(addprefix $(SRCS_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -o $@ -c $?

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(TEMP) $(OBJS) -lpthread

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

leak: TEMP+=$(LEAK)

leak: all

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus leak

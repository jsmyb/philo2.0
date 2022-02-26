# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 16:19:09 by lsoghomo          #+#    #+#              #
#    Updated: 2022/02/18 17:33:48 by lsoghomo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/philo.c \
		src/utils.c \
		src/threads.c \
#		src/checker.c \
#		src/thread_utils.c \

OBJS = $(SRCS:.c=.o)

GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0;0m

CC = gcc

RM = rm -rf

NAME = philo

CFLAGS = -Wall -Wextra -Werror

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN)DONE!$(RESET)"
clean:
		$(RM) $(OBJS)
fclean:
		$(RM) $(OBJS) $(NAME)
		@echo "$(RED)DELETED!$(RESET)"
re:		fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 15:43:19 by lburkins          #+#    #+#              #
#    Updated: 2024/05/17 14:16:03 by lburkins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo

SRCS		=		philo.c \
					philo_utils.c \
					error_handling.c \
					init.c

OBJS		=		$(SRCS:.c=.o)

HEADER		=		philo.h

CC			=		cc

RM			=		@rm -f

CFLAGS		=		-Wall -Wextra -Werror

ANSI_GREEN := \033[0;32m
ANSI_CYAN := \033[0;36m
ANSI_RESET := \033[0m

all:		 $(NAME)
	
%.o: %.c $(HEADER)
				@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo "** $(ANSI_GREEN)Philosophers Compiled$(ANSI_RESET) ✅ **"

clean:
				$(RM) $(OBJS)
				@echo "** $(ANSI_CYAN)Philosophers Cleaning Complete$(ANSI_RESET) 🧹 **"

fclean:		clean
				$(RM) $(NAME)
				@echo "** $(ANSI_CYAN)Philo F Cleaning Complete$(ANSI_RESET) 🧹 **"

re:			fclean all

.PHONY:		all clean fclean re
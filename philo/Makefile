	# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 15:29:33 by fdrudi            #+#    #+#              #
#    Updated: 2022/04/05 14:09:43 by mcerchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC			=	philosophers.c philo_utils.c lst_manage.c time.c routine.c\

OBJ			=	$(SRC:.c=.o)

CC			=	gcc -pthread

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

%.o:%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
			${RM} $(OBJ)

fclean: 	clean
			${RM} $(NAME) ${OBJ}

re:			fclean all

.PHONY:		all clean fclean re

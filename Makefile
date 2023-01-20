# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 10:14:02 by nali              #+#    #+#              #
#    Updated: 2023/01/07 18:17:48 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_containers

SRCS	= 

OPTION = 12

SRCS_STK = tests/stack/stack_test.cpp

OBJS	= ${SRCS:.cpp=.o}

OBJS_STK	= ${SRCS_STK:.cpp=.o}

CC		= c++

CFLAGS	= -Wall -Werror -Wextra -std=c++98

RM		= rm -f

all:	${NAME}

.c.o:	${CC} ${CFLAGS}  -I -c $< -o ${<:.cpp=.o}

${NAME}:	${OBJS}
		$(CC) ${CFLAGS} ${OBJS} -o $(NAME)

stack:	${OBJS_STK}
		$(CC) ${CFLAGS}  ${OBJS_STK} -o $(NAME) 
		$(file > file1)
			

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re .c.o
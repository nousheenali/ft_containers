# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 10:14:02 by nali              #+#    #+#              #
#    Updated: 2023/01/05 10:14:16 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= megaphone

SRCS	= megaphone.cpp

OBJS	= ${SRCS:.cpp=.o}

CC		= c++

CFLAGS	= -Wall -Werror -Wextra -std=c++98

RM		= rm -f

all:	${NAME}

.c.o:	${CC} ${CFLAGS} -I -c $< -o ${<:.cpp=.o}

${NAME}:	${OBJS}
		$(CC) ${CFLAGS} ${SRCS} -o $(NAME)
		rm ${OBJS}
			

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re .c.o
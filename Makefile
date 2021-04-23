# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 19:40:00 by mlebrun           #+#    #+#              #
#    Updated: 2021/04/23 11:08:25 by mlebrun          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_CHECKER = srcs/main_checker.c \
	   srcs/ft/ft_strlen.c \
	   srcs/ft/ft_strcpy.c \
	   srcs/ft/ft_strdup.c \
	   srcs/ft/ft_isdigit.c \
	   srcs/ft/ft_putstr.c \
	   srcs/gnl/gnl.c

SRCS_PUSH_SWAP = srcs/main_push_swap.c

OBJS_CHECKER = ${SRCS_CHECKER:.c=.o}

OBJS_PUSH_SWAP = ${SRCS_PUSH_SWAP:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes/

NAME1 = checker
NAME2 = push_swap

RM	= rm -rf

.c.o:		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME1} ${NAME2}

$(NAME1):	${OBJS_CHECKER}
			${CC} -o ${NAME1} ${OBJS_CHECKER} ${CFLAGS}

$(NAME2):	${OBJS_PUSH_SWAP}
			${CC} -o ${NAME2} ${OBJS_PUSH_SWAP} ${CFLAGS}

clean:
			${RM} ${OBJS_CHECKER}
			${RM} ${OBJS_PUSH_SWAP}

fclean:		clean
			${RM} ${NAME1}
			${RM} ${NAME2}

bonus:		${NAME1} ${NAME2}

re:			fclean all

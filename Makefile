# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 19:40:00 by mlebrun           #+#    #+#              #
#    Updated: 2021/05/18 14:40:19 by mlebrun          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/check_args.c \
	   srcs/instructions.c \
	   srcs/numbers.c \

SRCS_CHECKER = srcs/main_checker.c \
			   srcs/gnl.c

SRCS_PUSH_SWAP = srcs/main_push_swap.c

SRCS_FT = srcs/ft/ft_strlen.c \
	   srcs/ft/ft_strcpy.c \
	   srcs/ft/ft_strdup.c \
	   srcs/ft/ft_isdigit.c \
	   srcs/ft/ft_putstr.c \
	   srcs/ft/ft_strcmp.c

OBJS = ${SRCS:.c=.o}

OBJS_CHECKER = ${SRCS_CHECKER:.c=.o}

OBJS_PUSH_SWAP = ${SRCS_PUSH_SWAP:.c=.o}

OBJS_FT = ${SRCS_FT:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes/

NAME1 = checker
NAME2 = push_swap

RM	= rm -rf

.c.o:		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME1} ${NAME2}

$(NAME1):	${OBJS} ${OBJS_CHECKER} ${OBJS_CHECKER} ${OBJS_FT}
			${CC} -o ${NAME1} ${OBJS} ${OBJS_CHECKER} ${OBJS_FT} ${CFLAGS} -fsanitize=address

$(NAME2):	${OBJS} ${OBJS_PUSH_SWAP} ${OBJS_FT}
			${CC} -o ${NAME2} ${OBJS} ${OBJS_PUSH_SWAP} ${OBJS_FT}  ${CFLAGS} -fsanitize=address

clean:
			${RM} ${OBJS}
			${RM} ${OBJS_CHECKER}
			${RM} ${OBJS_PUSH_SWAP}
			${RM} ${OBJS_FT}

fclean:		clean
			${RM} ${NAME1}
			${RM} ${NAME2}

bonus:		${NAME1} ${NAME2}

re:			fclean all

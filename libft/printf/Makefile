# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 11:09:36 by tvillare          #+#    #+#              #
#    Updated: 2022/11/08 13:45:30 by tvillare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#                                                       FILES                 #
###############################################################################
CFILES		= \
			ft_printf.c \
			utils/ft_selectoption.c utils/ft_strchrp.c utils/ft_putstr.c \
			ft_options/ft_c.c ft_options/ft_di.c ft_options/ft_u.c \
			ft_options/ft_s.c ft_options/ft_x.c ft_options/ft_p.c
OBJS	=	${CFILES:.c=.o}

###############################################################################
#                                                   SETTINGS                  #
###############################################################################
NAME = libftprintf.a
HDRS = ft_printf.h

CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = ar
ARFLAGS = -rcs
RM = rm -f

###############################################################################
#                                                         OPTIONS             #
###############################################################################
all: ${NAME}

$(NAME):  $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.c.o:
		 ${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HDRS}

###############################################################################
clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re

include colors.mk
###############################################################################
#                                              FILES                          #
###############################################################################
include colors.mk

NAME = p

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -pthread
FSANITIZE = -fsanitize=address -g

SRCSDIR = ./srcs/
SRCSCFILES = ft_atoi.c ft_isdigit.c \
			main.c philo.c sniffer_philo.c check_input.c utils.c actions.c

#BINDIR = ${addprefix ${SRCSDIR}, builtins/}
#BINCFILES = ft_export.c ft_unset.c ft_pwd.c ft_cd.c ft_echo.c ft_env.c ft_exit.c builtin_utils.c


SRCS =	${addprefix ${SRCSDIR}, ${SRCSCFILES}} \
		#${addprefix ${BINDIR}, ${BINCFILES}} \

OBJS = ${SRCS:.c=.o}

LFT_NAME = libft.a
LIB_DIR = ./libft/

INC = -I ./includes/ -I ${LIB_DIR}includes/


RM = rm -rf
################################################################################
.PHONY: all re fclean clean test setup
################################################################################
all: ${NAME}

test: ${NAME}
	./${NAME}

retest: re
	./${NAME}

${NAME}: ${OBJS}
	@${CC}  ${CFLAGS} ${OBJS} -o ${NAME}
	@printf "${God} ${BIBlue}Mini${NoColor}🐚 de ${BIPurple}LaLora${NoColor}${God}\n"

${LFT_NAME}:
	@make -s -C ${LIB_DIR}

%.o: %.c
	@${CC} -c ${CFLAGS} $^ -o $@ ${INC}
	@printf "${BIGreen}[Compiled]${BIBlue} $^ ${NoColor}to ${BIPurple}$@ ${NoColor}                       \r"

re: fclean all

clean:
	@make -s -C ${LIB_DIR} clean
	@${RM} ${OBJS}
	@printf "${Bad}${BIRed}Delete *.o${NoColor}${Bad}\n"

fclean: clean
	@make -s -C ${LIB_DIR} fclean
	@${RM} ${NAME}
	@printf "${Bad}${BIRed}Delete ${NAME}${NoColor}${Bad}\n"


setup:
	@rm -rf $$HOME/.brew && git clone https://github.com/Homebrew/brew $$HOME/goinfre/.brew
	#echo 'export PATH=$$HOME/goinfre/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc
	@brew update
	@brew install readline
	@printf "${God}${BICyan}Install brew and library in MAC.${God}${NoColor}"
################################################################################


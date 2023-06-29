include colors.mk
###############################################################################
#                                              FILES                          #
###############################################################################
SRCSDIR = ./srcs/
SRCSCFILES = main.c  sniffer_philo.c check_input.c

UTILDIR = ${addprefix ${SRCSDIR}, utils/}
UTILFILES = ft_atoi.c utils.c ft_isdigit.c

PTHREADDIR = ${addprefix ${SRCSDIR}, pthread/}
PTHREADFILES = actions.c philo.c

SRCS =	${addprefix ${SRCSDIR}, ${SRCSCFILES}} \
		${addprefix ${UTILDIR}, ${UTILFILES}} \
		${addprefix ${PTHREADDIR}, ${PTHREADFILES}}

OBJS = ${SRCS:.c=.o}


INC = -I ./includes/

###############################################################################
#                                              SETTINGS                       #
###############################################################################
NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -pthread
FSANITIZE = -fsanitize=address -g

RM = rm -rf
################################################################################
.PHONY: all re fclean clean
###############################################################################
#                                              OPTIONS                        #
###############################################################################

all: ${NAME}

${NAME}: ${OBJS}
	@${CC}  ${CFLAGS} ${OBJS} -o ${NAME}
	@printf "\n${God}${BIGreen}[Create] ${BIBlue}Philo${NoColor}${NoColor}${God}\n"

${LFT_NAME}:
	@make -s -C ${LIB_DIR}

%.o: %.c
	@${CC} -c ${CFLAGS} $^ -o $@ ${INC}
	@printf "${BIGreen}[Compiled]${BIBlue} $^ ${NoColor}to ${BIPurple}$@ ${NoColor}                       \r"

re: fclean all

clean:
	@${RM} ${OBJS}
	@printf "${Bad}${BIRed}Delete *.o${NoColor}${Bad}\n"

fclean: clean
	@${RM} ${NAME}
	@printf "${Bad}${BIRed}Delete ${NAME}${NoColor}${Bad}\n"

################################################################################


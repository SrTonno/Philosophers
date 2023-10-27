include colors.mk

###############################################################################
#                                              FILES                          #
###############################################################################
SRCSDIR = ./srcs/
SRCSCFILES = main.c  sniffer_philo.c check_input.c

UTILDIR = ${addprefix ${SRCSDIR}, utils/}
UTILFILES = ft_atoi.c utils.c

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
#THREAD =  -fsanitize=thread -g -lpthread

RM = rm -rf
################################################################################
.PHONY: all re fclean clean test1 test2 test3 test4 test5 test_hard
###############################################################################
#                                              OPTIONS                        #
###############################################################################

all: ${NAME}

${NAME}: ${OBJS}
	@${CC}  ${CFLAGS} ${THREAD} ${OBJS} -o ${NAME}
	@printf "\n${God}${BIGreen}[Create] ${BIBlue}Philo${NoColor}${NoColor}${God}\n"

${LFT_NAME}:
	@make -s -C ${LIB_DIR}

%.o: %.c
	@${CC} -c ${CFLAGS}  $^ -o $@ ${INC}
	@printf "${BIGreen}[Compiled]${BIBlue} $^ ${NoColor}to ${BIPurple}$@ ${NoColor}                       \r"

re: fclean all

clean:
	@${RM} ${OBJS}
	@printf "${Bad}${BIRed}Delete *.o${NoColor}${Bad}\n"

fclean: clean
	@${RM} ${NAME}
	@printf "${Bad}${BIRed}Delete ${NAME}${NoColor}${Bad}\n"

###############################################################################
#                                              TEST                           #
###############################################################################
#MANDATORI
test1: all
	./philo 1 800 200 200 # mueren

test2: all
	./philo 5 800 200 200 # viven

test3: all
	./philo 5 800 200 200 7 #viven y cada uno come 7 veces

test4: all
	./philo 4 410 200 200 #viven

test5: all
	./philo 4 310 200 100 #mueren
#EXTRA
test_hard: all
	./philo 100 180 60 60 #extremo viven
################################################################################

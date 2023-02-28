include colors.mk
###############################################################################
#                                              FILES                          #
###############################################################################
CFILES		= \
			ft_atoi.c ft_isdigit.c \
			main.c philo.c sniffer_philo.c check_input.c utils.c actions.c
OBJS	=	${CFILES:.c=.o}

###############################################################################
#                                              SETTINGS                       #
###############################################################################
NAME = philo
HDRS = philo.h

NLIBRARY= libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
OPGRAFIC = -lmlx -framework OpenGL -framework AppKit
FSANITIZE = -fsanitize=address -g

AR = ar
ARFLAGS = -rcs
RM = rm -f

LIBFT = $(OLIBFT) $(OPRINTF) $(OGNL)

###############################################################################
#                                              OPTIONS                        #
###############################################################################
all: ${NAME}

${NAME}:  ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o $@ -pthread
	@echo "${God}${Green}Created '${NAME}'.${NoColor}"

git: fclean
	@echo "\t${BIPurple}>>Push To Git<<${NoColor}"
	@git remote -v | cut -d " " -f 1 | uniq
	@git add . ;
	@read -p "Name the commit: " commit ;\
	git commit -m "$$commit" ;\
	read -p "Check the files..." -t 20;
	@git push origin master ;

normi:
	@echo "${BICyan}>>Check Files with ${BIRed}ERROR${BICyan} norminette<<${NoColor}"
	@norminette -R CheckForbiddenSourceHeader | grep Error! | grep -v tester
	@echo "Total Errores $$(norminette -R CheckForbiddenSourceHeader | grep -v Error! | grep -v tester | wc -l)"

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

###############################################################################
clean:
		@${RM} ${OBJS}
		@echo "${Bad}${Red}Delete .o.${NoColor}"

fclean: clean
		@${RM} ${NAME}
		@echo "${Bad}${Red}Delete '${NAME}'.${NoColor}"

re: fclean all

help:
	@echo "${UGreen}Options of MakeFile:${NoColor}"
	@echo "Used: make [options]"
	@echo "\t${BICyan}Default:${NoColor} Created '${NAME}'"
	@echo "\t${IRed}clean:${NoColor} Delete '.o'."
	@echo "\t${BIRed}fclean:${NoColor} Delete'.o', '${NLIBRARY}'"
	@echo "\t${BICyan}re:${NoColor} Delete '.o', '${NLIBRARY}', '${NAME}' and creates '${NAME}'"
	@echo "\t${BIPurple}git:${NoColor} Push to git."
	@echo "\t${BICyan}normi:${NoColor} Check file with Error the norminette."
	@echo "MakeFile by ${UBlue}tvillare${NoColor}."

.PHONY = all clean fclean re help normi git

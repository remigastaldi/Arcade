##
## Makefile for Makefile in /home/gastal_r/rendu/cpp_arcade
##
## Made by
## Login   <gastal_r>
##
## Started on  Sat Feb 11 18:22:43 2017
## Last update Sat Feb 11 20:09:42 2017
##

ECHO            =       /bin/echo -e
DEFAULT         =       "\033[00m"
GREEN           =       "\033[0;32m"
TEAL            =       "\033[1;36m"
RED             =       "\033[1;31m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[1;34m"

CC              =       g++

RM              =       rm -f

NAME            =       arcade

CXXFLAGS	+=	-I./core/includes
CXXFLAGS	+=	-Wextra -Wall -W

SRC             =       core/src/main.cpp

OBJ             =       $(SRC:.cpp=.o)

all             :	title $(NAME)

title		:
			@make -C games/ --no-print-directory
			@make -C libs/ --no-print-directory
			@$(ECHO) $(RED)"\n\n\
\t  _|_|    _|_|_|      _|_|_|    _|_|    _|_|_|    _|_|_|_|	\n \
\t_|    _|  _|    _|  _|        _|    _|  _|    _|  _|		\n \
\t_|_|_|_|  _|_|_|    _|        _|_|_|_|  _|    _|  _|_|_|    	\n \
\t_|    _|  _|    _|  _|        _|    _|  _|    _|  _|        	\n \
\t_|    _|  _|    _|    _|_|_|  _|    _|  _|_|_|    _|_|_|_|  \n\n" $(DEFAULT)


$(NAME)         :	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS) && \
			 $(ECHO) $(YELLOW) "[OK]" $(BLUE) $(NAME) $(DEFAULT)  || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $(NAME)

clean           :
			@make clean -C games/ --no-print-directory
			@make clean -C libs/ --no-print-directory
			@rm -f $(OBJ)

fclean          :       clean
			@make fclean -C games/ --no-print-directory
			@make fclean -C libs/ --no-print-directory
			@$(RM) $(NAME)

re              :       fclean all

.PHONNY         :       all clean fclean re

.cpp.o		:
			@$(CC) $(CXXFLAGS) -c $< -o $@  && \
			 $(ECHO) $(YELLOW) "[OK]" $(BLUE) $< $(DEFAULT) || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

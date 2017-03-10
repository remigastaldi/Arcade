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
RED             =       "\033[0;31m"

CC              =       g++

RM              =       rm -f

CXXFLAGS	+=	-I./includes
CXXFLAGS	+=	-Wextra -Wall -W -fPIC -shared

SNNAME          =       ../lib_arcade_snake.so
SNSRC           =       src/lib_arcade_snake.cpp
SNOBJ           =       $(SNSRC:.cpp=.o)

all             :	title $(SNNAME)
			@cp $(SNNAME) ../../

title		:
			@$(ECHO) $(GREEN)GAME $(TEAL)LIBS$(DEFAULT)


$(SNNAME)       :	$(SNOBJ)
			@$(CC) -o $(SNNAME) $(SNOBJ) $(CXXFLAGS) && \
			 $(ECHO) $(GREEN) "[OK]" $(TEAL) $(SNNAME) $(DEFAULT)  || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $(SNNAME)

clean           :
			@rm -f $(SNOBJ)

fclean          :       clean
			@$(RM) $(SNNAME)
			@$(RM) ../$(SNNAME)

re              :       fclean all

.PHONNY         :       all clean fclean re

.cpp.o		:
			@$(CC) $(CXXFLAGS) -c $< -o $@  && \
			 $(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

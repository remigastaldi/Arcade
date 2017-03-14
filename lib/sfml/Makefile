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
YELLOW          =       "\033[1;33m"

CC              =       g++

RM              =       rm -f

CXXFLAGS	+=	-I./includes -I../../interfaces/
CXXFLAGS	+=	-Wextra -Wall -W -fPIC -shared
CXXFLAGS        +=      -lsfml-graphics -lsfml-window -lsfml-system

NCNAME          =       ../lib_arcade_sfml.so
NCSRC           =       src/LSfml.cpp
NCOBJ           =       $(NCSRC:.cpp=.o)

all             :	title $(NCNAME)
			@cp $(NCNAME) ../../

title		:
			@$(ECHO) $(YELLOW)LSFML $(DEFAULT)


$(NCNAME)         :	$(NCOBJ)
			@$(CC) -o $(NCNAME) $(NCOBJ) $(CXXFLAGS) && \
			 $(ECHO) $(GREEN) "[OK]" $(TEAL) $(NCNAME) $(DEFAULT)  || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $(NCNAME)

clean           :
			@rm -f $(NCOBJ)

fclean          :       clean
			@$(RM) $(NCNAME)
			@$(RM) ../$(NCNAME)

re              :       fclean all

.PHONNY         :       all clean fclean re

.cpp.o		:
			@$(CC) $(CXXFLAGS) -c $< -o $@  && \
			 $(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

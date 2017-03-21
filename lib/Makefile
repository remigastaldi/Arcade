##
## Makefile for Makefile in /home/gastal_r/rendu/cpp_arcade
##
## Made by
## Login   <gastal_r>
##
## Started on  Sat Feb 11 18:22:43 2017
## Last update Sat Feb 11 20:09:42 2017
##

all:
	@make -C ncurses/ --no-print-directory
	@make -C sfml/ --no-print-directory
	@make -C opengl/ --no-print-directory

clean:
	@make clean -C ncurses/ --no-print-directory
	@make clean -C sfml/ --no-print-directory
	@make clean -C opengl/ --no-print-directory

fclean:	clean
	@make fclean -C ncurses/ --no-print-directory
	@make fclean -C sfml/ --no-print-directory
	@make fclean -C opengl/ --no-print-directory

re: fclean all

.PHONNY: all clean fclean re

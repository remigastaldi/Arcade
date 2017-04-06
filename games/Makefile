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
	@make -C snake/
	@make -C solarfox/

clean:
	@make clean -C snake/
	@make clean -C solarfox/

fclean:	clean
	@make fclean -C snake/
	@make fclean -C solarfox/

re: fclean all

.PHONNY: all clean fclean re

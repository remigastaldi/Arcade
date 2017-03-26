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
	@make -C solar_fox/

clean:
	@make clean -C snake/
	@make clean -C solar_fox/

fclean:	clean
	@make fclean -C snake/
	@make fclean -C solar_fox/

re: fclean all

.PHONNY: all clean fclean re

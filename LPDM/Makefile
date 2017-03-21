##
## Makefile for Makefile in /home/hubet_t/rendu/cpp_arcade
##
## Made by
## Login   <hubert_i>
##
## Started on  Sat Feb 11 18:22:43 2017
## Last update Sat Feb 11 20:09:42 2017
##

all:
	@make -C ../
	@g++ main.cpp -l_arcade_snake -L../ -o la_putain_de_moulinette

clean:
	@rm la_putain_de_moulinette
	@make clean -C ../

fclean:	clean
	@make fclean -C ../

re: fclean all

.PHONNY: all clean fclean re

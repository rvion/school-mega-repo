NAME = program
CC   = g++
CXXFLAGS += -W -Wall -Wextra -O3 --std=c++0x
RM   = rm -f
SRC  = main.cpp
OBJ  = $(SRC:.cpp=.o)
SDL  = `sdl-config --libs --cflags`

all :  $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJ) $(SDL)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

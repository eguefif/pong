NAME=pong
CC=g++
FLAGS=-w
INCLUDE=-I./include -I./src
LIB=-lSDL2 -lSDL2_image -lSDL2_ttf

_SRC=main.cpp pong.cpp game.cpp menu.cpp remote.cpp local.cpp computer.cpp objects.cpp renderer.cpp
_OBJ=$(_SRC:.cpp=.o)
_INC=pong.h menu.h
SDIR=./src/
ODIR=./obj/
IDIR=./include/
SRC=$(addprefix $(SDIR), $(_SRC))
OBJ=$(addprefix $(ODIR), $(_OBJ))
INC=$(addprefix $(IDIR), $(_INC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ) $(LIB)

$(ODIR)%.o: $(SDIR)%.cpp $(INC)
	$(CC) $(INCLUDE) -c $< -o $@

.PHONY: clean re test
clean:
	rm -f $(ODIR)*.o $(NAME)

re: clean all

test:
	./$(NAME)

NAME=pong
CC=g++
FLAGS=-w
INCLUDE=-I./src
LIB=-lSDL2 -lSDL2_image -lSDL2_ttf

_SRC=main.cpp pong.cpp game.cpp menu.cpp remote.cpp local.cpp computer.cpp racket.cpp ball.cpp renderer.cpp utils.cpp
_OBJ=$(_SRC:.cpp=.o)
_INC=pong.h menu.h game.h remote.h computer.h racket.h ball.h renderer.h
SDIR=./src/
ODIR=./obj/
IDIR=./src/
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

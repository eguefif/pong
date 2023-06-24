NAME=Pong
CC=g++
INCLUDE=-I./include

_SRC=pong.cpp
_OBJ=$(_SRC:.cpp=.o)
SDIR=./src/
ODIR=./obj/
SRC=$(addprefix $(SDIR), $(_SRC))
OBJ=$(addprefix $(ODIR), $(_OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(SRC)

$(ODIR)%.o: $(SDIR)%.cpp
	$(CC) $(INCLUDE) -c $< -o $@

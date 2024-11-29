CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -Wall -c -I$(INC)
LFLAGS = -Wall -I$(INC)
OBJS = $(OBJ)/main.o 

EXE = $(BIN)/main

all: $(EXE) run

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/main.o: $(SRC)/main.cpp $(HDRS)
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(EXE) $(OBJS)

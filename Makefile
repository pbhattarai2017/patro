BIN := ./bin
INCLUDE := ./include
OBJ := ./obj
SRC := ./src
LIB := ./lib
MAIN := main

# main executable target
$(BIN)/main: $(OBJ)/main.o $(OBJ)/patro.o
	$(CC) -o $(BIN)/main $(OBJ)/main.o $(OBJ)/patro.o

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) -o $(OBJ)/main.o -c $(SRC)/main.c
	
$(OBJ)/patro.o: $(LIB)/patro/patro.c
	$(CC) -o $(OBJ)/patro.o -c $(LIB)/patro/patro.c

clean:
	$(RM) $(OBJ)/*
	$(RM) $(BIN)/*

structure:
	mkdir -p bin
	mkdir -p obj

install: $(BIN)/main
	echo "alias miti=\"${PWD}/bin/main\"" >> ~/.bash_aliases
	echo "alias patro=\"${PWD}/bin/main patro\"" >> ~/.bash_aliases
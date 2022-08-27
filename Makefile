BUILD := ./build
INCLUDE := ./include
OBJ := ./obj
SRC := ./src
MAIN := main

all: structure $(BUILD)/$(MAIN)
	$(BUILD)/$(MAIN)
	
$(BUILD)/$(MAIN): $(SRC)/$(MAIN).c
	$(CC) -o $(BUILD)/$(MAIN) $(SRC)/$(MAIN).c

clean:
	$(RM) $(OBJ)/*
	$(RM) $(BUILD)/*

structure:
	mkdir -p build
	mkdir -p obj

SRC_DIR=src
OBJ=Record.o DecisionTree.o main.o
EXE=main
CC=g++

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(SRC_DIR)/*

Record.o:
	$(CC) -c $(SRC_DIR)/Record.cpp

DecisionTree.o:
	$(CC) -c $(SRC_DIR)/DecisionTree.cpp

main.o:
	$(CC) -c $(SRC_DIR)/main.cpp

clean:
	rm -f *.o

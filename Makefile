CC = gcc
SRC = ann.c
OBJ = ann
FLAGS = -Wall -g -lm

all:
	$(CC) $(FLAGS) -o $(OBJ) $(SRC)
	./$(OBJ) -i datain



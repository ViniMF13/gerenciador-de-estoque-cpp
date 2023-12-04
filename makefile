CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++17
INCLUDES = -I . -I ./Include
OUTPUT_DIR = ./output
SRC_DIR = ./src


all: build run

clean:
	rm $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/main.exe

build: interface.o inventario.o item.o movimentacao.o main.o
	$(CC) $(CFLAGS) $(INCLUDES) $(OUTPUT_DIR)/*.o -o $(OUTPUT_DIR)/main 

run:
	$(OUTPUT_DIR)/main.exe

rebuild: clean build run

main.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o $(OUTPUT_DIR)/main.o

interface.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/Interface.cpp -o $(OUTPUT_DIR)/interface.o

inventario.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/Inventario.cpp -o $(OUTPUT_DIR)/inventario.o

item.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/Item.cpp -o $(OUTPUT_DIR)/item.o

movimentacao.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/Movimentacao.cpp -o $(OUTPUT_DIR)/movimentacao.o
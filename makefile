CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++17
INCLUDES = -I . -I ./Include
OUTPUT_DIR = ./output9

all: build

clean:
	rm $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/*.exe

build: main.o interface.o inventario.o item.o movimentacao.o main.exe

run:
	$(OUTPUT_DIR)/main.exe

rebuild: clean build run

main.exe: main.o
	$(CC) $(CFLAGS) $(INCLUDES) main.cpp -o $(OUTPUT_DIR)/main.exe

main.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o $(OUTPUT_DIR)/main.o

interface.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c Interface.cpp -o $(OUTPUT_DIR)/interface.o

inventario.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c Inventario.cpp -o $(OUTPUT_DIR)/inventario.o

item.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c Item.cpp -o $(OUTPUT_DIR)/item.o

movimentacao.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c Movimentacao.cpp -o $(OUTPUT_DIR)/movimentacao.o

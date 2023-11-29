CC = g++
CFLAGS = -Wall -Werror -pedantic
OUTPUT_DIR = ./output

all: main.exe

clean:
	rm $(OUTPUT_DIR)/*.*

buid: main.exe

run:
	$(OUTPUT_DIR)/main.exe

rebuild: clean build run

main.exe:
	$(CC) $(CFLAGS) -I . -I ./Include main.cpp -o $(OUTPUT_DIR)/main.exe

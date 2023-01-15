CC = gcc
LIB_DIR = ./lib/ #where your libraylib.a file is
INCL_DIR = ./include/

LINKERS =-L $(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm -ltmx -lxml2 -lzlibstatic
OUTPUT_FLAGS = -Wall -std=c99 -Wno-missing-braces
CFLAGS = -static -fdiagnostics-color=always

build_debug: main.o MapCollision.o
	$(CC) $(CFLAGS) -g -o demo $(OUTPUT_FLAGS) main.o MapCollision.o $(LINKERS)

build_static_lib: MapCollision.o
	ar rcs libraytmxcol.a MapCollision.o

main.o: main.c
	$(CC) -c main.c

MapCollision.o: MapCollision.c
	$(CC) -c MapCollision.c

clean: 
	rm -f demo *.o

run: 
	./demo

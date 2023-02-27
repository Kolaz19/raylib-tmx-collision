CC = gcc
LIB_DIR = ./lib/ #where your libraylib.a file is
INCL_DIR = ./include/
OBJ_DIR = ./object_files/

LINKERS =-L $(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm -ltmx -lxml2 -lzlibstatic
OUTPUT_FLAGS = -Wall -std=c99 -Wno-missing-braces
CFLAGS = -static -fdiagnostics-color=always

build_debug: $(OBJ_DIR)example.o $(OBJ_DIR)MapCollision.o
	$(CC) $(CFLAGS) -g -o demo $(OUTPUT_FLAGS) $(OBJ_DIR)example.o $(OBJ_DIR)MapCollision.o $(LINKERS)
	mv demo.exe ./example/

build_static_lib: MapCollision.o
	ar rcs libraytmxcol.a MapCollision.o

$(OBJ_DIR)example.o: ./example/example.c
	$(CC) -c ./example/example.c
	mv example.o $(OBJ_DIR)

$(OBJ_DIR)MapCollision.o: MapCollision.c
	$(CC) -c MapCollision.c
	mv MapCollision.o $(OBJ_DIR)

clean: 
	rm -f demo *.o

run: 
	./demo

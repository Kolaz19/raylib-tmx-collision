CC = gcc
LIB_DIR = ./lib/#where your libraylib.a file is
INCL_DIR = ./include/
OBJ_DIR = ./object_files/
EX_DIR = ./example/

LINKERS =-L $(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm -ltmx -lxml2 -lzlibstatic -lraytmxcol
OUTPUT_FLAGS = -Wall -std=c99 -Wno-missing-braces
CFLAGS = -static -fdiagnostics-color=always
DEBUG_FLAG = #-g

build_debug: $(OBJ_DIR)example.o $(LIB_DIR)libraytmxcol.a
	$(CC) $(CFLAGS) -g -o demo $(OUTPUT_FLAGS) $(OBJ_DIR)example.o $(LINKERS)
	mv demo.exe $(EX_DIR)

$(LIB_DIR)libraytmxcol.a: $(OBJ_DIR)MapCollision.o $(OBJ_DIR)TmxCollisionMapper.o
	ar rcs libraytmxcol.a $(OBJ_DIR)TmxCollisionMapper.o $(OBJ_DIR)MapCollision.o 
	mv libraytmxcol.a $(LIB_DIR)

$(OBJ_DIR)example.o: $(EX_DIR)example.c
	$(CC) -c $(DEBUG_FLAG) $(EX_DIR)example.c
	mv example.o $(OBJ_DIR)

$(OBJ_DIR)MapCollision.o: MapCollision.c
	$(CC) -c $(DEBUG_FLAG) MapCollision.c
	mv MapCollision.o $(OBJ_DIR)

$(OBJ_DIR)TmxCollisionMapper.o: TmxCollisionMapper.c
	$(CC) -c $(DEBUG_FLAG) TmxCollisionMapper.c
	mv TmxCollisionMapper.o $(OBJ_DIR)

clean: 
	rm -f $(OBJ_DIR)*.o $(EX_DIR)demo.exe $(LIB_DIR)libraytmxcol.a

run: 
	./demo

INCLUDE = -I/opt/homebrew/Cellar/sdl2/2.30.3/include -I/opt/homebrew/Cellar/sdl2_image/2.8.2_1/include
LIB = -L/opt/homebrew/Cellar/sdl2/2.30.3/lib -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib -lSDL2 -lSDL2_image
# SRC = src/
# OBJ = obj/
# TARGET_NAMES = main.o init.o texture.o input.o entity.o enemy.o update.o

# main: $(TARGET_NAMES)
# 	gcc $(TARGET_NAMES) -o main $(LIB)

# $(TARGET_NAMES): %.o: %.c
# 	gcc -c $< -o $@ $(INCLUDE)

# clean:
# 	rm -f *.o

NOME=main

CFILES=$(wildcard ./src/*.c)

HFILES=$(wildcard ./include/*.h)

OBJ=$(subst .c,.o,$(subst src,obj,$(CFILES)))

CC=gcc

CFLAGS=-c -W -Wall -I ./include

RM = rm -rf

all: object_dir $(NOME)
 
$(NOME): $(OBJ)
	$(CC) $^ -o $@ $(LIB)
 
./obj/%.o: ./src/%.c ./include/%.h
	$(CC) $< $(CFLAGS) -o $@ $(INCLUDE)
 
object_dir:
	@mkdir -p obj
 
clean:
	$(RM) ./obj/*.o $(NOME) *~
 
purge: clean
	$(RM) ./obj

.PHONY: all clean
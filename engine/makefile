CC=g++
STD=-std=c++17
CFLAGS=-Wall -Wextra
INC_Path=-I./libs -I./libs/lua
SRC=src/*.cpp \
    src/Game/*.cpp \
    src/ECS/*.cpp \
	src/AssetManager/*.cpp \
	src/ControllerManager/*.cpp \
	src/SceneManager/*.cpp
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.3
EXEC=game_engine

build:
	$(CC) $(STD) $(CFLAGS) $(INC_Path) $(SRC) $(LFLAGS) -o $(EXEC) 

run:
	./$(EXEC)

clean:
	rm -f $(EXEC)	
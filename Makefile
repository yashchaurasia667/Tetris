CFLAGS = -Wall -Wextra
LIBS = -lraylib
DEPENDENCIES = src/grid.cpp src/colors.cpp src/block.cpp src/position.cpp src/game.cpp

default: tetris

tetris: src/grid.h src/grid.cpp src/main.cpp
	mkdir -p build
	g++ $(CFLAGS) -o build/tetris $(DEPENDENCIES) src/main.cpp $(LIBS)

clean: build
	rm -rf build

run: build/tetris
	build/tetris
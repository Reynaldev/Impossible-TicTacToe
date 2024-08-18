SOURCE = $(shell find . -name "*.cpp" -type f -print0 | xargs -0)
LINKER = -lsfml-window -lsfml-graphics -lsfml-system

install:
	g++ $(SOURCE) -o build/linux/it3 $(LINKER)
	cp -r ImpossibleTicTacToe/assets/* build/linux/assets/*

copy-assets-only:
	cp -r ImpossibleTicTacToe/assets/* build/linux/assets/*
SRC=main.c
BIN=main

$(BIN): $(SRC)
	gcc -g -std=c99 main.c `sdl-config --cflags --libs` -I ./dll/include -L ./dll/lib -Wl,-rpath,./dll/lib -o main -lm -lSDL_mixer -lSDL_image -lSDL_ttf

clean:
	rm -f $(BIN)

PLATFORM ?= DESKTOP # or WEB

FLAGS := -Wall -Wextra -Werror -Wno-unused-parameter -Wno-gnu-folding-constant
CC := gcc -std=c99 -DUSE_SDL2_MIXER_BACKEND
LIBS := `pkg-config sdl2 --libs --cflags` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

ifeq ($(PLATFORM),WEB)
	CC := emcc -Wl,--fatal-warnings
	FLAGS += -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s ASSERTIONS -s ALLOW_MEMORY_GROWTH -s SDL2_MIXER_FORMATS='["ogg", "wav"]' -s SDL2_IMAGE_FORMATS='["png"]' -s EXPORTED_RUNTIME_METHODS="['ccall']" -s EXIT_RUNTIME=1 -s FORCE_FILESYSTEM=1 --preload-file assets/ --shell-file shell.html -DPLATFORM_WEB -Os
  LIBS :=
	TARGET := index.html
else
	TARGET := app
  LIBS := $(LIBS)
endif

all: $(TARGET)

$(TARGET): ./source/*.c
	$(CC) $^ -o $@ $(LIBS) $(FLAGS)

clean:
	rm -f $(TARGET) index.js index.wasm index.data index.html

.PHONY: clean

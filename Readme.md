# Gato - SDL2 Game Toolkit

This is Lightweight abstraction on top of SDL2. Bit outdated, but still useable for building 2D games (especially for game jams, for wasm distribution)

It abstracts:
- sprite frame, animated sprites, parallax system, font, particles, audio, immediate mode ui, scene transitions, 2d collision solvers, input management.

Supports WebAssembly and native compilation to Linux and Macos (Windows support is trivial since its SDL)

in the dk_game.c you can find simple local multiplayer game demo.

# Build

Install following deps
- sdl2
- sdl2_image
- sdl2_ttf
- sdl2_mixer (or use local audio engine see makefile)

In order to target wasm you need to install Emscripten toolchain

```
# for native compilation
make 

# for WebAssembly (expects Emscripten toolchain)
make -e PLATFORM=WEB
```


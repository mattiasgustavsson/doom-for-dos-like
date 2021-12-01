![build](https://github.com/mattiasgustavsson/doom-for-dos-like/workflows/build/badge.svg)

# doom-for-dos-like
This is a quick but fairly complete version of the original DOOM ported to 
the [dos-like framework](https://github.com/mattiasgustavsson/dos-like).
The data included is for original DOOM shareware version.

It can be built as a Windows executable or as WebAssembly to run in a browser.
I have not tried running it for Linux or Mac, but the code builds at least.

You can try the web version at https://mattiasgustavsson.com/wasm/doom

## Operating

While running, you can use F11 to toggle between fullscreen and windowed mode.

To start in windowed mode, add the flag -w or --window to the commandline when launching.


## Building

dos-like does not make use of any complicated build systems - a simple command line call to the compiler is
all that is needed to build both the Doom code and the engine itself.


### Windows

From a Visual Studio Developer Command Prompt:

```
  cl source\doom.c source\dos.c
```  


### Mac

```
  clang source/doom.c source/dos.c `sdl2-config --libs --cflags` -lGLEW -framework OpenGL -lpthread
```

SDL2 and GLEW are required - if you don't have them installed you can do so with Homebrew by running
```
  brew install sdl2 glew  
```


### Linux

```
  gcc source/doom.c source/dos.c `sdl2-config --libs --cflags` -lGLEW -lGL -lm -lpthread
```

SDL2 and GLEW are required - if you don't have them installed you can do so on Ubuntu (or wherever `apt-get` is available) by running
```
  sudo apt-get install libsdl2-dev
  sudo apt-get install libglew-dev
```


### WebAssembly

```
  wasm\node wasm\wajicup.js -embed doom1.wad doom1.wad -template template.html source\doom.c source\dos.c doom.html
```

A WebAssembly build environment is required. You can download it (for Windows) here: [github.com/mattiasgustavsson/dos-like/releases/tag/wasm-env](https://github.com/mattiasgustavsson/dos-like/releases/tag/wasm-env).
Unzip it so that the `wasm` folder in the zip file is at your repository root. 

The wasm build environment is a compact distribution of [node](https://nodejs.org/en/download/), [clang/wasm-ld](https://releases.llvm.org/download.html),
[WAjic](https://github.com/schellingb/wajic) and [wasm system libraries](https://github.com/emscripten-core/emscripten/tree/main/system).


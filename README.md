# nodes-frontend
Data structure and algorithm visualizer

# To compile yourself:
1. Get yourself SFML 2.5.1 libraries (window, graphics, system) somewhere
2. Create `.env` file in project root (i.e alongside this README file) and specify SFML_PREFIX (see `.env.example`) where your libs are located
3. Important! Project compiles using MSYS MinGW, change all `-G "MSYS Makefiles"` flags inside of `./configure.sh` if necessary
4. Launch `./configure.sh` script: this will create release config with example program
5. Run `./build.sh --run` to compile and run the program
Program itself and necessary resources will be placed into `SFML_PREFIX/bin` directory

All code and tests for example program are located in `main.cpp`

# To compile examples:
1. Get yourself SFML 2.5.1 libraries (window, graphics, system) somewhere
2. Create `.env` file in project root (i.e alongside this README file) and specify SFML_PREFIX (see `.env.example`) where your libs are located
3. Go to `examples` and choose program
4. Run `compile.sh`. It will create and copy binary into the `SFML_PREFIX/bin` folder

# To use library with your programs do the following:
1. Create static library:
    1. Compile all resources (steps 3 and 4 from compilation steps, use `./build.sh` instead to avoid program launch)
    2. Run `./couple.sh`. This will create `libnf.a`
2. Move files where your program is located so your environment would consist of:
     * your program
     * `libnf.a`
     * `sfml-graphics-2.dll`/`sfml-graphics-2.so`
     * `sfml-system-2.dll`/`sfml-system-2.so`
     * `sfml-window-2.dll`/`sfml-window-2.so`
     * `resources` folder (available in root project)
3. Compile (e.g. using gcc):
```
g++ binary_tree.cpp -o binary_tree.exe
    -I ./include
    -I <SFML_include_dir>
    -L <SFML_lib_dir>
    ./libnf.a -lsfml-window -lsfml-graphics -lsfml-system
```

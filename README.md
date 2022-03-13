# nodes-frontend
Data structure visualizer

Static linking (temporary, Windows):
```
g++ -o del_main del_main.cpp ./build/src/libnv.a -I./include -L../../libraries/SFML-2.5.1/lib/ -lsfml-window -lsfml-graphics -lsfml-system -I../../libraries/SFML-2.5.1/include/ -lopengl32
```
Copy into dir with SFML DLLs.

#TODO: Resolve manual linking of: SFML (widdow, graphics, system), OpenGL

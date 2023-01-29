# nodes-frontend
Data structure visualizer

Static linking (temporary, Windows):
```
g++ -o del_main del_main.cpp ./build/src/libnfend.a -I./include -L../../libraries/SFML-2.5.1/lib/ -lsfml-window -lsfml-graphics -lsfml-system -I../../libraries/SFML-2.5.1/include/ -lopengl32
```
Copy into dir with SFML DLLs.

#TODO: Resolve manual linking of: SFML (window, graphics, system), OpenGL

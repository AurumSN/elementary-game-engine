g++ -std=c++23 -g main.cpp src/*.cpp -o main.exe -I./include/ -L./lib/ -DUNICODE -ld3d11 -ld3dcompiler -ldirectxtex -luuid -lole32 -lgomp
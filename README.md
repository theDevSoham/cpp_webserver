# Strating the application

* Make sure that you have any c++ compiler installed like `g++`. If not `mingw` provides a toolchain for this purpose

## Starting automatically using script

* Run using the script provided. Use `./run.sh server.cpp -lwsock32` on windows and `./run.sh server.cpp` on Linux or Mac and uncomment the `line 2` of `server.cpp` before running.

## Starting manually

* Run `g++ server.cpp -lwsock32` for Windows and `./run.sh server` for Linux and Mac.

* After compilation, if there's no error, run `./server`
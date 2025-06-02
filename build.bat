@echo off
rmdir /s /q build
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
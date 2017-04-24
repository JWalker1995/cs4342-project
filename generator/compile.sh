#!/bin/sh
g++ -g -O0 src/*.cpp src/*/*.cpp -std=c++11 -o generator
./generator data.csv > ../webpage/func.js

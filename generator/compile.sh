#!/bin/sh
g++ -g -O0 src/*.cpp -std=c++11 -o func_generator
./func_generator data.csv > ../webpage/func.js

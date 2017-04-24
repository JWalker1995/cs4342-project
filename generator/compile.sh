#!/bin/sh
cd "$(dirname "$0")/src"
g++ -g -O0 *.cpp */*.cpp -std=c++11 -o ../generator
cd ..
./generator data.csv > ../webpage/func.js

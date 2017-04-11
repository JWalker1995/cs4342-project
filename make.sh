#!/bin/sh

g++ -g -O0 main.cpp -o naive_bayes
./naive_bayes data.csv > func.js


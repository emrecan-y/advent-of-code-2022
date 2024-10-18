# adventOfCode2022

This repository contains my solutions for Advent of Code 2022. My goal is to use C++ to deepen my understanding of the language.

# Compiling and Executing

Every .cpp file of each day has a main funtion, so they can be compiled and executed similarly to this example;

```bash
g++ day_1.cpp advent_day.cpp -std=c++17 && ./a.out
```

Useful compile options;

```bash
-g                  #to compile with debugging symbols
-fsanitize=address  #to check for memory errors
```

Useful run options;

```bash
./a.out & leaks $!  #to check for memory leaks
time ./a.out        #to measure the execution time
```

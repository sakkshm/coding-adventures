# `wc` CLI tool

**wc** is a simple command-line utility that mimics the Unix `wc` tool. It counts lines, words, characters, and bytes in text files or from standard input. This project follows the Unix philosophy of building simple, composable tools with clean interfaces.

---

## Features

* Count **lines**: `-l`
* Count **words**: `-w`
* Count **bytes**: `-c`
* Count **characters**: `-m`
* Default behavior (no option): shows **lines, words, and bytes**
* Supports reading from **stdin**

---

## Usage

```bash
# Compile
g++ -std=c++17 -o wc wc.cpp

# Count lines
./wc -l file.txt

# Count words
./wc -w file.txt

# Count bytes
./wc -c file.txt

# Count characters
./wc -m file.txt

# Default: lines, words, bytes
./wc file.txt

# Reading from stdin
cat file.txt | ./wc -l
```

---

## Building Instructions

1. Make sure you have a C++ compiler (g++ or clang++) installed.
2. Open terminal in the directory containing `wc.cpp`.
3. Compile the code:

```bash
g++ -std=c++17 -o wc wc.cpp
```

4. Run the executable using the examples above.

---

## Notes

* The `-m` option counts characters one by one using `fstream::get`.
* File pointers are reset after each counting operation to allow multiple counts in the same execution.
* If no filename is provided, `wc` can read input from `stdin`.

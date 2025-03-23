# CFG Processor

## Overview
This project implements a CFG Processor that:
- Reads a Context-Free Grammar (CFG) from a file (`input.txt`).
- Applies **Left Factoring** and **Left Recursion Elimination**.
- Computes **FIRST and FOLLOW sets**.
- Constructs an **LL(1) Parsing Table**.
- Outputs results to `output.txt`.

## Instructions for Running on Linux
1. Ensure you have `g++` installed:
```bash
sudo apt-get install g++
```

2. Navigate to the directory containing the files:
```bash
cd /path/to/your/files
```

3. Compile all `.cpp` files with the necessary headers:
```bash
g++ -o cfg_processor cfg_processor.cpp -std=c++17
```

4. Run the program:
```bash
./cfg_processor
```

5. View the results in `output.txt`.

## File Structure
- `CFG.h`: Handles the grammar processing, including transformations, set computation, and parsing table generation.
- `CFGReader.h`: Reads CFGs from a file and initializes the CFG structure.
- `ProductionRule.h`: Manages production rules for the CFG.
- `State.h`: Defines terminals, non-terminals, and special symbols.
- `StateSet.h`: Manages **FIRST** and **FOLLOW** sets.
- `ParsingTable.h`: Builds and displays the LL(1) Parsing Table.
- `cfg_processor.cpp`: Main program file.

## Example Input
```
S -> a A | a B | S b | c
A -> A a | b
```

## Output Example
```
FIRST(S) = { epsilon, a }
FIRST(A) = { }
FIRST(B) = { }
FIRST(S') = { epsilon }

FOLLOW(S) = { $ }
FOLLOW(A) = { }
FOLLOW(B) = { }
FOLLOW(S') = { epsilon, b }
```

## Authors
- Tauha Imran 
- Husain Ali Zaidi



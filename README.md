## Advent of Code 2025
### Requirements:
- CMake 3.26+
- C++20 compiler
- Ninja

### Building:
- First clone the repo and enter the new directory: 
```bash
git clone https://github.com/dsch7705/aoc2025.git
cd aoc2025
```

- Then run the build commands: 
```bash
cmake -B build -G Ninja .
cmake --build build
```

### Usage:
- Place puzzle inputs in the corresponding ```src/dayX``` folder as ```input.txt```
- Run the corresponding ```build/bin/dayX-puzzleY``` executable
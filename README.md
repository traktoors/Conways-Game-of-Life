# Conway's Game of Life
Conway's Game of Life is a cellular automaton devised by mathematician John Conway in 1970. It simulates the evolution of a grid of cells, each of which can be "alive" or "dead." The state of each cell in the next generation is determined by a set of simple rules based on the number of alive neighbors. These rules can lead to complex patterns and behaviors, such as oscillators, gliders, and stable structures, despite the game's simplicity. It is a famous example of how complex systems can emerge from simple, deterministic rules.

* Any live cell with two or three live neighbors survives to the next generation.
* Any dead cell with exactly three live neighbors becomes alive (this is called reproduction).
* All other live cells die (due to underpopulation or overpopulation).
* All other dead cells remain dead.

## How to build & run
### Using Visual Studio
To build and run in Visual Studio:
1. Clone ```git clone https://github.com/traktoors/Conways-Game-of-Life.git``` -> Open GameOfLife.sln -> Press <kbd>F5<\kbd>

### Using Make
```
cd Conways-Game-of-Life/build
cmake ../
make
../GameOfLife
```

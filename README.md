# PlayerVisualization
Entity Visualization for Ecosystem

## Build instructions

```
git clone https://github.com/DarkStar1997/PlayerVisualization
cd PlayerVisualization
mkdir build
cmake -S . -B build/
cmake --build build/
```

## Run instructions
```
./build/run/main
```
Check with **--help**  to know about all the available options.

## Dependancies

This project uses [SFML](https://github.com/SFML/SFML) for rendering. It's downloaded and build automatically by CMake. Make sure OpenGL is installed on the system and can be used by SFML.

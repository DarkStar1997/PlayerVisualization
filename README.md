
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

## Tips

1. It's highly recommended to use Ninja as the build system for faster incremental builds. To do so, install ninja for your distribution and then modify the cmake generation command to `cmake -GNinja -S . -B build/`


<style>.embed-container { position: relative; padding-bottom: 56.25%; height: 0; overflow: hidden; max-width: 100%; } .embed-container iframe, .embed-container object, .embed-container embed { position: absolute; top: 0; left: 0; width: 100%; height: 100%; }</style><div class='embed-container'><iframe src='https://www.youtube.com/embed/_YiR8NbAGhk' frameborder='0' allowfullscreen></iframe></div>

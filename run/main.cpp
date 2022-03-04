#include <game.hpp>
#include <chrono>
#include <thread>
#include <argh.h>
#include <fmt/core.h>

int main(int argc, char **argv)
{
    std::string help_text = "./main [options]\n"
                            "--num=100 [number of entities]\n"
                            "--size=10.0 [size of each entity]\n"
                            "--origin [entities spawn at the origin which is the top-left corner. By default they spawn randomly]\n";
    argh::parser cmdl;
    cmdl.parse(argc, argv);
    int num_entities = 100;
    bool isRandom = true;
    float size = 10.0;
    if(cmdl["help"])
    {
        fmt::print("{}\n", help_text);
        exit(0);
    }
    if(cmdl("num"))
        num_entities = std::stoi(cmdl("num").str());
    if(cmdl["origin"])
        isRandom = false;
    if(cmdl("size"))
        size = std::stof(cmdl("size").str());
    
    Game game;
    game.spawnEntities(num_entities, isRandom, size);
    game.clock.restart();
    game.direction_clock.restart();
    while(game.running() && !game.getEndGame())
    {
        game.deltaTime = game.clock.restart();
        game.update();
        game.render();
    }
}

#include <game.hpp>
#include <chrono>
#include <thread>

int main()
{
    Game game;
    game.spawnEntities(1000);
    game.clock.restart();
    game.direction_clock.restart();
    while(game.running() && !game.getEndGame())
    {
        game.deltaTime = game.clock.restart();
        game.update();
        game.render();
    }
}

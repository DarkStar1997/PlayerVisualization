#include <game.hpp>
#include <chrono>
#include <thread>

int main()
{
    Game game;
    game.spawnEntities(50000);
    game.clock.restart();
    while(game.running() && !game.getEndGame())
    {
        game.deltaTime = game.clock.restart();
        game.update();
        game.render();
    }
}

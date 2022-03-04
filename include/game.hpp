#include <memory>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Entity;

class Game
{
private:
    sf::RenderWindow * window;
    std::vector<uint8_t> direction;
    bool endGame;
    sf::Event event;
    std::mt19937_64 rng;
    std::uniform_int_distribution<uint8_t> direction_gen;
    
    void initVars();
    void initWindow();
    void pollEvents();

public:
    Game();
    ~Game();
    sf::Clock clock;
    sf::Clock direction_clock;
    sf::Time deltaTime;
    std::vector<Entity> entities;
    const bool running() const;
    const bool getEndGame() const;
    void update();
    void render();
    void spawnEntities(size_t n, bool isRandom = true, float size = 10.0);
};

#include <SFML/Window/Event.hpp>
#include <game.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <entity.hpp>

Game::Game()
{
    this->initVars();
    this->initWindow();
    rng.seed(std::random_device()());
    direction_gen = std::uniform_int_distribution<uint8_t>(0, 1);
}

Game::~Game()
{
    delete this->window;
}

void Game::initVars()
{
    this->endGame = false;
}

void Game::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    this->window = new sf::RenderWindow(sf::VideoMode(), "Game", sf::Style::Fullscreen, settings);
    this->window->setFramerateLimit(60);
}

const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

void Game::render()
{
    this->window->clear();
    for(auto& entity : entities) entity.draw(window);
    this->window->display();
}

void Game::pollEvents()
{
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                {
                    window->close();
                    break;
                }
            case sf::Event::KeyPressed:
                {
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        window->close();
                        break;
                    }
                    
                    break;
                }
        }
    }
}

void Game::spawnEntities(size_t n, bool isRandom, float size)
{
    entities.reserve(n);
    std::uniform_int_distribution<int> spawn_position_x(0, window->getSize().x);
    std::uniform_int_distribution<int> spawn_position_y(0, window->getSize().y);
    for(size_t i = 0; i < n; i++)
    {
        if(isRandom)
            entities.emplace_back(i % colors.size() + 2, spawn_position_x(rng), spawn_position_y(rng), size);
        else
            entities.emplace_back(i % colors.size() + 2, 0, 0, size);
        entities.back().setColor(colors[i % colors.size()]);
    }
    direction = std::vector<uint8_t>(entities.size(), 0);
}

void Game::update()
{
    pollEvents();
    if(endGame == false)
    {
        // update direction every 0.1 seconds
        if(direction_clock.getElapsedTime().asSeconds() >= 0.1)
        {
            direction = std::vector<uint8_t>(entities.size(), 0);
            for(size_t i = 0; i < entities.size(); i++)
            {
                uint8_t tmp = 0, restricted_directions = 0;
                // stuck in left boundary
                if(entities[i].shape.getPosition().x <= 0.0f)
                {
                    restricted_directions |= Direction::left;
                }
                // stuck in right boundary
                else if (entities[i].shape.getPosition().x + entities[i].shape.getGlobalBounds().width >= window->getSize().x)
                {
                    restricted_directions |= Direction::right;
                }
                // stuck in top boundary
                if (entities[i].shape.getPosition().y <= 0.f)
                {
                    restricted_directions |= Direction::up;
                }
                // stuck in bottom boundary
                else if (entities[i].shape.getPosition().y + entities[i].shape.getGlobalBounds().height >= window->getSize().y)
                {
                    restricted_directions |= Direction::down;
                }
                
                tmp = direction_gen(rng);
                direction[i] = direction[i] | (tmp == 1 ? Direction::up : Direction::down);
                tmp = direction_gen(rng);
                direction[i] = direction[i] | (tmp == 1 ? Direction::left : Direction::right);
                
                direction[i] &= ~restricted_directions;
            }
            direction_clock.restart();
        }
        for(size_t i = 0; i < entities.size(); i++)
            entities[i].move(direction[i], window, (float)deltaTime.asMilliseconds());
    }
}

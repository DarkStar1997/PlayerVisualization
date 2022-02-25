#include <SFML/Window/Event.hpp>
#include <game.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>

Game::Game()
{
    this->initVars();
    this->initWindow();
    rng.seed(std::random_device()());
    direction_gen = std::uniform_int_distribution<uint8_t>(0, 1);
    direction_clock.restart();
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
    //this->window->setFramerateLimit(60);
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
    //this->entity.draw(window);
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

void Game::spawnEntities(size_t n)
{
    entities.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        entities.emplace_back();
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
        if(direction_clock.getElapsedTime().asSeconds() >= 0.5)
        {
            direction = std::vector<uint8_t>(entities.size(), 0);
            for(size_t i = 0; i < entities.size(); i++)
            {
                uint8_t tmp = direction_gen(rng);
                direction[i] = direction[i] | (tmp == 1 ? Direction::up : Direction::down);
                tmp = direction_gen(rng);
                direction[i] = direction[i] | (tmp == 1 ? Direction::left : Direction::right);
            }
            direction_clock.restart();
        }
        //entities[0].update(window, 1);
        for(size_t i = 0; i < entities.size(); i++)
            entities[i].move(direction[i], window, 1);
        //entity.move(direction, window, 1);
        //entity.update(window, 1);
        //entity.update(window, deltaTime.asSeconds());
    }
}

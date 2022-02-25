#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

extern std::vector<sf::Color> colors;

namespace Direction
{
    extern uint8_t up;
    extern uint8_t down;
    extern uint8_t right;
    extern uint8_t left;
};

class Entity
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    void updateWindowBoundsCollision(const sf::RenderTarget * target);
    void updateInput(const float & dTime);
public:
    Entity();
    void update(const sf::RenderTarget * target, const float & dTime);
    void draw(sf::RenderTarget * target);
    void move(const uint8_t & direction, const sf::RenderTarget * target, const float & dTime);
    void moveUp(const float & dTime);
    void moveDown(const float & dTime);
    void moveRight(const float & dTime);
    void moveLeft(const float & dTime);
    void setColor(sf::Color);
};


#endif /* ENTITY_HPP */

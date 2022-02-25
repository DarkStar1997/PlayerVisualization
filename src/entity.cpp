#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <entity.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>

std::vector<sf::Color> colors = {sf::Color::Blue,
                                 sf::Color::Red,
                                 sf::Color::Green,
                                 sf::Color::Yellow,
                                 sf::Color::Magenta,
                                 sf::Color::White
                                };

namespace Direction
{
    uint8_t up = 0x01;
    uint8_t down = 0x02;
    uint8_t right = 0x04;
    uint8_t left = 0x08;
};

Entity::Entity()
{
    shape = sf::CircleShape(15.0f);
    velocity = {0.5, 0.5};
    acceleration = {0.1, 0.1};
}

Entity::Entity(int num, const int& x, const int& y)
{
    shape = sf::CircleShape(5.0f, num);
    //shape.setPosition({(float)x, (float)y});
    velocity = {0.05, 0.05};
    acceleration = {0.01, 0.01};
}

void Entity::draw(sf::RenderTarget * target)
{
    target->draw(this->shape);
}

void Entity::move(const uint8_t& direction, const sf::RenderTarget * target, const float & dTime)
{
    if(direction & Direction::up)
    {
        velocity.y -= (acceleration.y * dTime);
        moveUp(dTime);
    }

    else if(direction & Direction::down)
    {
        velocity.y += (acceleration.y * dTime);
        moveDown(dTime);
    }

    if(direction & Direction::right)
    {
        velocity.x += (acceleration.x * dTime);
        moveRight(dTime);
    }
    else if(direction & Direction::left)
    {
        velocity.x -= (acceleration.x * dTime);
        moveLeft(dTime);
    }
    updateWindowBoundsCollision(target);
}

void Entity::moveUp(const float & dTime)
{
    shape.move({0, -std::abs(velocity.y)});
    shape.setPosition({shape.getPosition().x, shape.getPosition().y - velocity.y * dTime});
}

void Entity::moveDown(const float & dTime)
{
    shape.move({0, std::abs(velocity.y)});
    //shape.setPosition({shape.getPosition().x, shape.getPosition().y + velocity.y * dTime});
}

void Entity::moveLeft(const float & dTime)
{
    shape.move({-std::abs(velocity.x), 0});
    //shape.setPosition({(float)shape.getPosition().x + (velocity.x * dTime), (float)shape.getPosition().y});
}

void Entity::moveRight(const float & dTime)
{
    shape.move({std::abs(velocity.x), 0});
    //shape.setPosition({(float)shape.getPosition().x + velocity.x * dTime, (float)shape.getPosition().y});
}

void Entity::update(const sf::RenderTarget * target, const float & dTime)
{
    updateInput(dTime);
    updateWindowBoundsCollision(target);
}

void Entity::updateInput(const float & dTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        fmt::print("pos_x: {} pos_y: {}\n", shape.getPosition().x, shape.getPosition().y);
        fmt::print("v_x: {} v_y: {}\n", velocity.x, velocity.y);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        velocity.y -= (acceleration.y * dTime);
        moveUp(dTime);
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        velocity.y += (acceleration.y * dTime);
        moveDown(dTime);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += (acceleration.x * dTime);
        moveRight(dTime);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= (acceleration.x * dTime);
        moveLeft(dTime);
    }
}

void Entity::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	//Left
	if (this->shape.getPosition().x < 0.f)
    {
        shape.setPosition({0.f, shape.getPosition().y});
    }
	//Right
	if (shape.getPosition().x + shape.getGlobalBounds().width > target->getSize().x)
    {
        shape.setPosition({target->getSize().x - shape.getGlobalBounds().width, shape.getPosition().y});
    }
	//Top
	if (shape.getPosition().y < 0.f)
    {
        shape.setPosition({shape.getPosition().x, 0.f});
    }
	//Bottom
	if (shape.getPosition().y + shape.getGlobalBounds().height > target->getSize().y)
    {
        shape.setPosition({shape.getPosition().x, (float)target->getSize().y - shape.getGlobalBounds().height});
    }
}

void Entity::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

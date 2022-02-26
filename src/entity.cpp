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

Entity::Entity(int num, const int& x, const int& y)
{
    const float initialSize = 10.0f;
    shape = num >= 3 ? sf::CircleShape(initialSize, num) : sf::CircleShape(initialSize);
    shape.setPosition({(float)x, (float)y});
    velocity = {4, 4};
    acceleration = {0.001, 0.001};
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
}

void Entity::moveDown(const float & dTime)
{
    shape.move({0, std::abs(velocity.y)});
}

void Entity::moveLeft(const float & dTime)
{
    shape.move({-std::abs(velocity.x), 0});
}

void Entity::moveRight(const float & dTime)
{
    shape.move({std::abs(velocity.x), 0});
}

void Entity::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	uint8_t tmp_direction = 0;
    //Left
	if (this->shape.getPosition().x < 0.f)
    {
        shape.setPosition({0.f, shape.getPosition().y});
        tmp_direction |= Direction::right;
    }
	//Right
	if (shape.getPosition().x + shape.getGlobalBounds().width > target->getSize().x)
    {
        shape.setPosition({target->getSize().x - shape.getGlobalBounds().width, shape.getPosition().y});
        tmp_direction |= Direction::left;
    }
	//Top
	if (shape.getPosition().y < 0.f)
    {
        shape.setPosition({shape.getPosition().x, 0.f});
        tmp_direction |= Direction::down;
    }
	//Bottom
	if (shape.getPosition().y + shape.getGlobalBounds().height > target->getSize().y)
    {
        shape.setPosition({shape.getPosition().x, (float)target->getSize().y - shape.getGlobalBounds().height});
        tmp_direction |= Direction::up;
    }
}

void Entity::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

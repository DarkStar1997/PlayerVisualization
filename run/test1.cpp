#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <chrono>
#include <random>
#include <thread>
#include <fmt/core.h>
#include <fmt/ranges.h>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    // create the window
    sf::RenderWindow window(sf::VideoMode(), "My window", sf::Style::Fullscreen, settings);
    sf::CircleShape shape(180.0f, 3);
    std::uniform_int_distribution<int> dis_x(0, window.getSize().x), dis_y(0, window.getSize().y);
    std::uniform_int_distribution<int> dis_rgb(0, 255);
    std::mt19937_64 rng{std::random_device()()};
    sf::Clock clock;
    std::vector<float> dTimes;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
        }

        // clear the window with black color
        //window.clear(sf::Color::Black);
        window.clear();

        // draw everything here...
        // window.draw(...);
        
        shape.setFillColor(sf::Color(dis_rgb(rng), dis_rgb(rng), dis_rgb(rng)));
        //shape.setPosition(dis_x(rng), dis_y(rng));
        window.draw(shape);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // end the current frame
        window.display();
        dTimes.push_back(deltaTime.asMilliseconds());
    }

    fmt::print("{}\n", dTimes);
    return 0;
}

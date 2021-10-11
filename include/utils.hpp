#ifndef SRC_HELPERS_UTILS_HPP_INCLUDED
#define SRC_HELPERS_UTILS_HPP_INCLUDED

#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>

#define say(something) {std::cout << something <<std::endl;}

namespace Utils
{
    template <typename T>
    T get_random_number(T from, T to);
    sf::Vector2f getMousePosf(const sf::RenderWindow &window);
}

#endif // SRC_HELPERS_UTILS_HPP_INCLUDED

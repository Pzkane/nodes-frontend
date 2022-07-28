#ifndef SRC_HELPERS_UTILS_HPP_INCLUDED
#define SRC_HELPERS_UTILS_HPP_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include "SafeQueue.hpp"

#ifdef DEBUG
#define say(something) {std::cout << something <<std::endl;}
#else
#define say(something) {}
#endif

#define error(message) {std::cout << "ERR: " << message << std::endl;}

namespace Utils
{
    template <typename T>
    T get_random_number(T from, T to);
    sf::Vector2f getMousePosf(const sf::RenderWindow &window);
}

#endif // SRC_HELPERS_UTILS_HPP_INCLUDED

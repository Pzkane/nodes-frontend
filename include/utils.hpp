#ifndef SRC_HELPERS_UTILS_HPP_INCLUDED
#define SRC_HELPERS_UTILS_HPP_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include "SafeQueue.hpp"

#ifdef DEBUG
#define say(something) {std::cout << something << std::endl;}
#define spit(something) {std::cout << something << " ";}
#else
#define say(something)
#define spit(something)
#endif

#define error(message) {std::cout << "ERR: " << message << std::endl;}

namespace nf {

constexpr float pi = 3.1415926;
constexpr float radian = 180 / pi;

namespace Utils
{
    /**
     * Get random number in range (distribution: mt19937)
     * @param from T
     * @param to T
    */
    template <typename T>
    T get_random_number(T from, T to);
    /**
     * Retrieve mouse position inside of a window
     * @param window sf::RenderWindow&
    */
    sf::Vector2f getMousePosf(const sf::RenderWindow &window);
    void delay(unsigned int ms);
}

};

/**
 * Helper for sf::Vector2f output onto outstream
*/
std::ostream& operator<<(std::ostream& out, const sf::Vector2f& vec);

#endif // SRC_HELPERS_UTILS_HPP_INCLUDED

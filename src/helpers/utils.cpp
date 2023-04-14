#include <random>
#include <chrono>
#include "utils.hpp"

namespace nf {

namespace Utils {

template <typename T>
T get_random_number(T from, T to) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(from, to);

    return dist(rng);
}

sf::Vector2f getMousePosf(const sf::RenderWindow &window) {
    return sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void delay(unsigned int ms) {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point end;
    do {
        end = std::chrono::system_clock::now();
        /* do nothing during interval */
    } while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < ms);
}

template int get_random_number<int>(int, int);
template float get_random_number<float>(float, float);

}; // namespace Utils

}; // namespace nf

std::ostream& operator<<(std::ostream& out, const sf::Vector2f& vec) {
    out << "[ " << vec.x << ", " << vec.y << " ]";
    return out;
}

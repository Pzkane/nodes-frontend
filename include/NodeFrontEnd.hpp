#ifndef SRC_API_NODEFRONTEND_HPP_INCLUDED
#define SRC_API_NODEFRONTEND_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class NodeFrontEnd
{
    sf::Color m_backgroundColor = sf::Color::Black;
    int init(const sf::VideoMode &video_mode, const char *title);

public:
    NodeFrontEnd(const sf::VideoMode &video_mode, const char *title);
    NodeFrontEnd();
    ~NodeFrontEnd() = default;
    void setWindowColor(const sf::Color &color);
};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED

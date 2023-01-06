#ifndef SRC_ENTITIES_LABEL_HPP_INCLUDED
#define SRC_ENTITIES_LABEL_HPP_INCLUDED

#include <string>
#include <SFML/Graphics.hpp>

namespace nf {

class Label : public sf::Text {
private:
    sf::RectangleShape m_box;
public:
    void setPosition(const sf::Vector2f& pos);
    void setPosition(float x, float y);
    const sf::RectangleShape& getBox() const { return m_box; }
};

}; // namespace nf

#endif // SRC_ENTITIES_LABEL_HPP_INCLUDED
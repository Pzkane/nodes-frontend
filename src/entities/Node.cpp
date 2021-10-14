#include "Node.hpp"
#include "Connector.hpp"
#include "utils.hpp"

Node::Node(float radius, std::size_t pointCount) : CircleShape(radius, pointCount)
{
    const sf::Vector2f center = CircleShape::getPosition();
    const float R = CircleShape::getRadius();
    sf::CircleShape::setOrigin(center.x + R, center.y + R);
}

void Node::update(const sf::RenderWindow &window, EventFlags &ef)
{
    text.setPosition(getPosition());
    CircleShape::setEventFlags(ef);
    checkMousePointer(window);

    if (mouseInside(Utils::getMousePosf(window)) && ef.f_rmb)
        if (!ef.p_start_node && ef.p_end_node != this)
        {
            say("START_NODE");
            ef.p_start_node = this;
        }
        else if (!ef.p_end_node && ef.p_start_node != this)
        {
            say("END_NODE");
            ef.p_end_node = this;
        }
}

void Node::draw(sf::RenderWindow &window)
{
    window.draw(*this);
    window.draw(text);
}

void Node::setText(const std::string &text)
{
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Black);
}

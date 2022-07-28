#include <algorithm>

#include "Node.hpp"
#include "Connector.hpp"
#include "utils.hpp"

Node::Node(float radius, std::size_t pointCount) : CircleShape(radius, pointCount, 50)
{
    const sf::Vector2f center = CircleShape::getPosition();
    const float R = CircleShape::getRadius();
    sf::CircleShape::setOrigin(center.x + R, center.y + R);

    auto setHelloText = [&](){
        setText("Hello!");
    };

    CircleShape::setCallback(setHelloText);
    text.setFont(Flags::font);
    text.setScale(0, 0);
}

void Node::update(const sf::RenderWindow &window, EventFlags &ef)
{
    updateText();
    CircleShape::setEventFlags(ef);
    checkMousePointer(window);

    if (mouseInside(Utils::getMousePosf(window)))
    {
        if (ef.f_rmb)
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

        if (ef.f_lalt)
        {
            for (auto &&conn : m_conns)
            {
                conn->enf.f_del = true;
            }
            enf.f_del = true;
        }

        if (ef.f_ralt)
        {
            invokeCallback();
        }
    }
}

void Node::updateText()
{
    const float PADDING = 0.3f;
    text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 1.4));
    text.setPosition(getPosition());
    const float D = 2 * sf::CircleShape::getRadius();
    const sf::FloatRect l_bounds = text.getLocalBounds();
    const sf::Vector2f sizeScale(l_bounds.width / D + PADDING, l_bounds.height / D + PADDING);
    const float maxScale = std::max(sizeScale.x, sizeScale.y);
    if (maxScale > 1)
        text.setScale(1 / maxScale, 1 / maxScale);
    else
    {
        text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height * 1.4));
        text.setScale(1, 1);
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
    this->text.setFillColor(sf::Color::White);
}

void Node::pushConnector(Connector *const conn)
{
    m_conns.push_back(conn);
}

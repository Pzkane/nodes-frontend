#include <algorithm>

#include "Node.hpp"
#include "Connector.hpp"
#include "LoopFlags.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"

using namespace nf;

Node::Node(float radius, std::size_t pointCount) : CircleShape(radius, pointCount, 50)
{
    const sf::Vector2f center = CircleShape::getPosition();
    const float R = CircleShape::getRadius();
    sf::CircleShape::setOrigin(center.x + R, center.y + R);

    auto setHelloText = [&](){
        setText("Hello!");
    };

    CircleShape::setCallback(setHelloText);
    text.setFont(ff.font);
    text.setScale(0, 0);
}

void Node::update(sf::RenderWindow &window, EventFlags &ef)
{
    updateText();
    setEventFlags(ef);
    trackMousePointer(window);

    if (mouseInside(Utils::getMousePosf(window)))
    {
        m_hovering = true;
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
            enf.f_delete_self = true;

        if (ef.f_ralt)
        {
            invokeCallback();
        }
    } else
        m_hovering = false;
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
    if (lf.f_t_ep_done) return;
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
}

void Node::pushConnNode(Node *const node)
{
    m_connected_nodes.push_back(node);
}

std::list<Node*> Node::getConnectedNodes() const
{
    return m_connected_nodes;
}


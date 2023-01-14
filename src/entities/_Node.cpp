#include <algorithm>

#include "_Node.hpp"
#include "Edge.hpp"
#include "LoopFlags.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"
#include "MouseCache.hpp"

using namespace nf;

unsigned _Node::id = 0;

_Node::_Node(float radius, std::size_t pointCount) : RADIUS(radius), CircleShape(radius, pointCount, 50)
{
    const sf::Vector2f center = CircleShape::getPosition();
    sf::CircleShape::setOrigin(center.x + RADIUS, center.y + RADIUS);
    sf::CircleShape::setOutlineThickness(1);
    sf::CircleShape::setOutlineColor(sf::Color(75, 75, 75));
    sf::CircleShape::setFillColor({220, 220, 220});

    auto setHelloText = [&](){
        setText(std::to_string(id));
    };

    CircleShape::setCallback(setHelloText);
    m_text.setFont(ff.font);
    m_text.setScale(0, 0);
    m_text.setFillColor(sf::Color::Black);
}

void _Node::update(const sf::RenderWindow &window, EventFlags &ef)
{
    updateText();
    setEventFlags(ef);
    trackMousePointer(window);

    if (mouseInside(Utils::getMousePosf(window)))
    {
        Mouse& m = MouseCache::getInstance(window)->gMouse;
        if (ef.f_lmb)
        {
            if (m.isCaptureEmpty())
                m.captureEntity(this);
        } else {
            // say((m.getEntity() == this));
            if (m.getEntity() == this)
                m.releaseEntity();
        }

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

void _Node::updateText()
{
    const float PADDING = 0.3f;
    m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 1.4));
    m_text.setPosition(getPosition());
    const float D = 2 * sf::CircleShape::getRadius();
    const sf::FloatRect l_bounds = m_text.getLocalBounds();
    const sf::Vector2f sizeScale(l_bounds.width / D + PADDING, l_bounds.height / D + PADDING);
    const float maxScale = std::max(sizeScale.x, sizeScale.y);
    if (maxScale > 1)
        m_text.setScale(1 / maxScale, 1 / maxScale);
    else
    {
        m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height * 1.4));
        m_text.setScale(1, 1);
    }
}

void _Node::draw(sf::RenderWindow &window)
{
    window.draw(*this);
    window.draw(m_text);
}

void _Node::setText(const std::string &text)
{
    if (lf.f_t_ep_done || lf.f_t_delete_active_scene) return;
    m_text.setString(text);
}

void _Node::setTextColor(const sf::Color& clr)
{
    m_text.setFillColor(clr);
}

void _Node::pushConnNode(_Node *const node)
{
    m_connected_nodes.push_back(node);
}

std::list<_Node*> _Node::getConnectedNodes() const
{
    return m_connected_nodes;
}


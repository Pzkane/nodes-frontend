#include <algorithm>

#include "NodeImpl.hpp"
#include "Edge.hpp"
#include "LoopFlags.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"
#include "MouseCache.hpp"
#include "ActionObserver.hpp"
#include "ActionObservable.hpp"

using namespace nf;

unsigned NodeImpl::id = 0;

NodeImpl::NodeImpl(Observable * hlNode, float radius, std::size_t pointCount, const std::size_t ms)
    : m_hl_node(hlNode), RADIUS(radius), CircleShape(radius, pointCount), Clickable(ms)
{
    const sf::Vector2f center = CircleShape::getPosition();
    sf::CircleShape::setOrigin(center.x + RADIUS, center.y + RADIUS);
    sf::CircleShape::setOutlineThickness(1);
    sf::CircleShape::setOutlineColor(sf::Color(75, 75, 75));
    sf::CircleShape::setFillColor({220, 220, 220});

    auto setHelloText = [&](){
        // setText(std::to_string(id));
    };

    setRMBCallback(setHelloText);
    m_text.setFont(ff.font);
    m_text.setScale(0, 0);
    m_text.setFillColor(sf::Color::Black);
}

void NodeImpl::update(const sf::RenderWindow &window, EventFlags &ef)
{
    updateText();
    setEventFlags(ef);
    trackMousePointer(window);

    if (m_destroy) {
        enf.f_delete_self = true;
        return;
    }
   
    Mouse& m = MouseCache::getInstance(window)->gMouse;
    if (mouseInside(Utils::getMousePosf(window)) && m_isVisible)
    {
        // For dragging
        if (ef.f_lmb)
        {
            if (m.isCaptureEmpty())
                m.captureEntity(this);
        } else {
            if (m.getEntity() == this)
                m.releaseEntity();
        }

        // For contextual actions
        m_hovering = true;
        if (ef.f_rmb) {
            if (m.isCaptureEmpty())
                m.captureEntity(this);
            if (m.getEntity() == this) {
                invokeRMBCallback();
                ActionObservable *p = new ActionObservable{m_hl_node};
                ActionObserver::getInstance()->setOriginAction(p);
                ActionObserver::getInstance()->performOriginAction();
                // Reset RMB flag to get 1 click, not press
                ef.f_rmb = false;
            }
            /*
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
            */
        }

        // For destroying
        if (ef.f_lalt)
            enf.f_delete_self = true;
    } else
        m_hovering = false;
}

void NodeImpl::updateText()
{
    const float PADDING = 0.3f;
    m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 1.4));
    m_text.setPosition(getPosition());
    // Diameter
    const float D = 2 * sf::CircleShape::getRadius();
    const sf::FloatRect l_bounds = m_text.getLocalBounds();
    // Scale text size and position to fit into node
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

void NodeImpl::draw(sf::RenderWindow &window)
{
    window.draw(*this);
    window.draw(m_text);
}

void NodeImpl::setText(const std::string &text)
{
    if (lf.f_t_ep_done || lf.f_t_delete_active_scene) return;
    m_text.setString(text);
}

void NodeImpl::setTextColor(const sf::Color& clr)
{
    m_text.setFillColor(clr);
}

void NodeImpl::setVisibility(const bool state) {
    m_isVisible = state;
}

void NodeImpl::pushConnNode(NodeImpl *const node)
{
    m_connected_nodes.push_back(node);
}

const std::list<NodeImpl*>& NodeImpl::getConnectedNodes() const
{
    return m_connected_nodes;
}

bool NodeImpl::isVisible() const {
    return m_isVisible;
}

void NodeImpl::destroy() {
    m_destroy = true;
}

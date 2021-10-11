#include "Node.hpp"
#include "Connector.hpp"
#include "utils.hpp"

Node::Node(float radius, std::size_t pointCount) : CircleShape(radius, pointCount)
{
    const sf::Vector2f center = CircleShape::getPosition();
    const float R = CircleShape::getRadius();
    sf::CircleShape::setOrigin(center.x + R, center.y + R);
}

Connector* Node::connectTo(Node *const p_node)
{
    Connector *conn = new Connector();
    conn->start(this);
    conn->end(p_node);
    p_connector_end = &conn->line[0];
    p_node->p_connector_end = &conn->line[1];
    return conn;
}

void Node::update(const sf::RenderWindow &window, EventFlags &ef)
{
    CircleShape::setEventFlags(ef);
    checkMousePointer(window);
    if (p_connector_end)
        p_connector_end->position = getPosition();
    else if (mouseInside(Utils::getMousePosf(window)) && ef.f_rmb)
        if (!ef.p_start_node && ef.p_end_node != this)
            ef.p_start_node = this;
        else if (!ef.p_end_node && ef.p_start_node != this)
            ef.p_end_node = this;
}

#include "Node.hpp"
#include "Connector.hpp"
#include "utils.hpp"

Node::Node(float radius, std::size_t pointCount) : CircleShape(radius, pointCount)
{
    const sf::Vector2f center = CircleShape::getPosition();
    const float R = CircleShape::getRadius();
    sf::CircleShape::setOrigin(center.x + R, center.y + R);
}

Node::~Node()
{
    if (m_connectors.size())
    {
        for (auto it = m_connectors.begin(); it != m_connectors.end();)
        {
            auto tmp_ = it;
            ++it;
            if (tmp_->conn)
            {
                tmp_->p_connector_end = nullptr;
                delete tmp_->conn;
                tmp_->conn = nullptr;
            }
        }
    }
}

Connector* Node::connectTo(Node *const p_node)
{
    say("CONNECTOR CREATED");
    Connector *conn = new Connector();
    m_connectors.push_back({conn, &conn->line[0]});
    p_node->m_connectors.push_back({conn, &conn->line[1]});
    return conn;
}

void Node::update(const sf::RenderWindow &window, EventFlags &ef)
{
    CircleShape::setEventFlags(ef);
    checkMousePointer(window);
    if (m_connectors.size())
        for (auto connRef : m_connectors)
            connRef.p_connector_end->position = getPosition();
    
    if (mouseInside(Utils::getMousePosf(window)) && ef.f_rmb)
        if (!ef.p_start_node && ef.p_end_node != this)
            {say("START_NODE"); ef.p_start_node = this;}
        else if (!ef.p_end_node && ef.p_start_node != this)
            {say("END_NODE"); ef.p_end_node = this;}
}

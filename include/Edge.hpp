#ifndef SRC_ENTITIES_EDGE_HPP_INCLUDED
#define SRC_ENTITIES_EDGE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "NodeImpl.hpp"
#include "Line.hpp"

namespace nf {

/* Used for payloads (edge connection) */
struct NodeRef
{
    NodeImpl *start = nullptr;
    NodeImpl *end = nullptr;
};

/**
 * @brief Main class for generic edge implementation which connects 2 nodes
*/
class Edge : public Entity, public Line
{
    void init(sf::Color color);
protected:
    NodeRef m_nodeRef;

    friend class NodeImpl;
public:
    explicit Edge(sf::Color color = sf::Color::Black);
    Edge(NodeImpl *const &start_node, NodeImpl *const &end_node, sf::Color color = sf::Color::Black);
    virtual ~Edge() = default;

    /**
     * Assign nodes to edge endings
     * @param start_node NodeImpl *const&
     * @param end_node NodeImpl *const&
    */
    void setNodeEndings(NodeImpl *const &start_node, NodeImpl *const &end_node);
    NodeRef& getNodeEndings() const;

    /**
     * Get SFML line
     * @returns const sf::VertexArray&
    */
    const sf::VertexArray& getDrawable() const;
    /**
     * Get visiblity state
     * @returns bool
    */
    bool isVisible() const;
    /**
     * Check if given position is under mouse pointer
     * @param position sf::Vector2f &
    */
    bool mouseInside(const sf::Vector2f &position) override;
    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_EDGE_HPP_INCLUDED
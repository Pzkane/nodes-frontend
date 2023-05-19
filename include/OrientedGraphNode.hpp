#ifndef SRC_API_ORIENTEDGRAPHNODE_HPP_INCLUDED
#define SRC_API_ORIENTEDGRAPHNODE_HPP_INCLUDED

#include "GraphNode.hpp"

namespace nf {
/**
 * @brief Represents single node of a oriented graph
*/
template <class C, typename T>
class OrientedGraphNode : virtual public GraphNode<C,T>
{
protected:
    void connectNodes(C* lnode) override {
        Node::m_api->connectOrientedNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
    }
public:
    explicit OrientedGraphNode(NodeFrontEnd *api, bool visible = true) : GraphNode<C,T>(api, visible) {}
};

};

#endif // SRC_API_ORIENTEDGRAPHNODE_HPP_INCLUDED

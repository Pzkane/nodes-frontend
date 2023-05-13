#ifndef SRC_API_WEIGHTEDGRAPHNODE_HPP_INCLUDED
#define SRC_API_WEIGHTEDGRAPHNODE_HPP_INCLUDED

#include <map>
#include <sstream>
#include "GraphNode.hpp"

namespace nf {
/**
 * @brief Represents single node of a singly linked list
*/
template <class C, typename T>
class WeightedGraphNode : public GraphNode<C,T>
{
protected:
    std::map<int, float> m_weights;
    void connectNodes(C* lnode) override {
        Node::m_api->connectWeightNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()), (*m_weights.find(lnode->ID)).second);
    }
public:
    explicit WeightedGraphNode(NodeFrontEnd *api, bool visible = true) : GraphNode<C,T>(api, visible) {}

    /**
     * Add neighbor to this graph node
     * @param lnode C*
     * @param weight float
    */
    void addNeighbor(C* lnode, float weight)
    {
        bool result = GraphNode<C,T>::addNeighbor(lnode, true, false);
        if (result) {
            setWeight(lnode, weight);
            connectNodes(lnode);
        }
    }

    void addNeighbor(C& lnode, float weight) {
        C* ptr_lnode = &lnode;
        addNeighbor(ptr_lnode, weight);
    }

    /**
     * Remove neighbor from this graph node
     * @param lnode C* to be removed
    */
    void removeNeighbor(C* lnode) {
        bool result = GraphNode<C,T>::removeNeighbor(lnode);
        if (result) {
            m_weights.erase(lnode->ID);
        }
    }

    void removeNeighbor(C& lnode) {
        C* ptr_lnode = &lnode;
        removeNeighbor(ptr_lnode);
    }

    /**
     * Set weight in a direction of a `lnode`
     * @param lnode C* of a neighboring node
     * @param weight float
     * @param doSameForOpposite to avoid recursion during node decoupling, true by default
    */
    void setWeight(C* lnode, float weight, bool doSameForOpposite = true) {
        if (lnode == nullptr || lnode == this) return;
        m_weights[lnode->ID] = weight;
        if (doSameForOpposite)
            lnode->setWeight(dynamic_cast<C*>(this), weight, false);
    }

    /**
     * Return weight in a direction of a `lnode`
     * @param *lnode
    */
    float getWeight(C* lnode) {
        auto record = m_weights.find(lnode->ID);
        if (record != m_weights.end()) {
            return m_weights[lnode->ID];
        } else {
            std::ostringstream err;
            err << "WeightedGraphNode " << lnode->ID << " is not a neighbor!";
            throw std::runtime_error(err);
        }
    }
};

};

#endif // SRC_API_WEIGHTEDGRAPHNODE_HPP_INCLUDED

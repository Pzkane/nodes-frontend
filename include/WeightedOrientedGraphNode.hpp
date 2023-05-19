#ifndef SRC_API_WEIGHTEDORIENTEDGRAPHNODE_HPP_INCLUDED
#define SRC_API_WEIGHTEDORIENTEDGRAPHNODE_HPP_INCLUDED

#include "OrientedGraphNode.hpp"
#include "WeightedGraphNode.hpp"

namespace nf {
/**
 * @brief Represents single node of a oriented graph
*/
template <class C, typename T>
class WeightedOrientedGraphNode : public OrientedGraphNode<C,T>, public WeightedGraphNode<C,T>
{
protected:
    void connectNodes(C* lnode) override {
        Node::m_api->connectWeightOrientedNodes(
            Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()),
            (*WeightedGraphNode<C,T>::m_weights.find(lnode->ID)).second
        );
    }
public:
    explicit WeightedOrientedGraphNode(NodeFrontEnd *api, bool visible = true)
        : GraphNode<C,T>(api, visible), OrientedGraphNode<C,T>(api, visible), WeightedGraphNode<C,T>(api, visible) {}

    /**
     * Add neighbor to this graph node
     * @param lnode C*
     * @param weight float
    */
    void addNeighbor(C* lnode, float weight) {
        WeightedGraphNode<C,T>::addNeighbor(lnode, weight);
    }

    void addNeighbor(C& lnode, float weight) {
        C* ptr_lnode = &lnode;
        WeightedOrientedGraphNode<C,T>::addNeighbor(ptr_lnode, weight);
    }

    /**
     * Remove neighbor from this graph node
     * @param lnode C* to be removed
    */
    void removeNeighbor(C* lnode) {
        WeightedGraphNode<C,T>::removeNeighbor(lnode);
    }

    void removeNeighbor(C& lnode) {
        C* ptr_lnode = &lnode;
        WeightedOrientedGraphNode<C,T>::removeNeighbor(ptr_lnode);
    }

    /**
     * Set weight in a direction of a `lnode`
     * @param lnode C* of a neighboring node
     * @param weight float
    */
    void setWeight(C* lnode, float weight) {
        WeightedGraphNode<C,T>::setWeight(lnode, weight);
    }

    /**
     * Return weight in a direction of a `lnode`
     * @param *lnode
    */
    float getWeight(C* lnode) {
        return WeightedGraphNode<C,T>::getWeight();
    }
};

};

#endif // SRC_API_WEIGHTEDORIENTEDGRAPHNODE_HPP_INCLUDED

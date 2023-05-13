#ifndef SRC_API_GRAPHNODE_HPP_INCLUDED
#define SRC_API_GRAPHNODE_HPP_INCLUDED

#include <map>
#include "GenericNode.hpp"
#include "Overlay.hpp"
#include "MouseCache.hpp"

namespace nf {
/**
 * @brief Represents single node of a graph
*/
template <class C, typename T>
class GraphNode : public GenericNode<T>
{
    static inline unsigned iter_id = 0;
protected:
    std::map<int, C*> m_neighbors;
    virtual void connectNodes(C* lnode) {
        Node::m_api->connectNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
    }
public:
    const unsigned ID;
    explicit GraphNode(NodeFrontEnd *api, bool visible = true) : ID(iter_id++), GenericNode<T>(api, LayoutType::Random, visible) {}

    /**
     * Add neighbor to this graph node
     * @param lnode
     * @return true whenever neighbor was added
    */
    bool addNeighbor(C* lnode, bool doSameForOpposite = true, bool performConnect = true)
    {
        Node::nodeSanityCheck();
        if (lnode == this) return false;
        if (lnode != nullptr) {
            m_neighbors.insert({lnode->ID, lnode});
            if (doSameForOpposite) {
                if (performConnect)
                    connectNodes(lnode);
                lnode->GraphNode::addNeighbor(dynamic_cast<C*>(this), false);
            }
            return true;
        }
        return false;
    }

    bool addNeighbor(C& lnode, bool doSameForOpposite = true, bool performConnect = true) {
        C* ptr_lnode = &lnode;
        return GraphNode::addNeighbor(ptr_lnode, doSameForOpposite, performConnect);
    }

    /**
     * Remove neighbor from this graph node
     * @param lnode to be removed
     * @param doSameForOpposite to avoid recursion during node decoupling, true by default
    */
    bool removeNeighbor(C* lnode, bool doSameForOpposite = true) {
        auto setGrEl = m_neighbors.find(lnode->ID);
        if (setGrEl == m_neighbors.end()) return false;
        if (doSameForOpposite) {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>((*setGrEl).second->getInnerNode()));
            lnode->GraphNode::removeNeighbor(dynamic_cast<C*>(this), false);
        }
        m_neighbors.erase(setGrEl);
        return true;
    }

    bool removeNeighbor(C& lnode, bool doSameForOpposite = true) {
        C* ptr_lnode = &lnode;
        return GraphNode::removeNeighbor(ptr_lnode, doSameForOpposite);
    }

    /**
     * Get next current node's neighbors
     * @returns C*
    */
    const std::map<int, C*>& getNeighbors() {
        Node::nodeSanityCheck();
        return m_neighbors;
    };

    /**
     * Apply actions on contextual menu press
    */
    void invoke() override {
        Overlay* gn_ui = this->m_overlay.createResource();
        gn_ui->createWrapper(Container{
            sf::Vector2f{90, 44},
            sf::Vector2f{MouseCache::getInstance(
                    *Node::m_api->getWindow()
                )->gMouse.getPosition(*Node::m_api->getWindow())},
            sf::Vector2i{}});
        gn_ui->addContainer(
            ///
            /// Container: takes last highlighted Graph node and connects to the current
            ///
            Container{"addNeighbor", [&](){
                    this->addNeighbor(dynamic_cast<C*>(Node::m_api->getSelectedNode()->getObservable()));
                }, false,
                sf::Vector2f{90, 20}, gn_ui->getWrapper()->getPosition(), sf::Vector2i{10, 10}}
        );
        auto selectedNodeImpl = dynamic_cast<C*>(Node::m_api->getSelectedNode()->getObservable());
        /// Perform neighbor removal for node that is currently being selected
        if (selectedNodeImpl && m_neighbors.find(selectedNodeImpl->ID) != m_neighbors.end()) {
            gn_ui->addContainer(
                ///
                /// Container: removes pointer to one of the neighbors.
                ///
                Container{"removeNeighbor", [&](){ 
                        this->removeNeighbor(dynamic_cast<C*>(Node::m_api->getSelectedNode()->getObservable()));
                    }, false,
                    sf::Vector2f{90, 20}, {gn_ui->getWrapper()->getPosition().x, gn_ui->getWrapper()->getPosition().y+22}, sf::Vector2i{10, 10}}
            );
        }
        Node::m_api->mergeOverlay(*gn_ui);
    }
};

};

#endif // SRC_API_GRAPHNODE_HPP_INCLUDED

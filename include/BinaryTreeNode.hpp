#ifndef SRC_API_BINARYTREENODE_HPP_INCLUDED
#define SRC_API_BINARYTREENODE_HPP_INCLUDED

#include "GenericNode.hpp"
#include "Overlay.hpp"
#include "MouseCache.hpp"

namespace nf {
/**
 * @brief Represents single node of a binary tree
 * 
 * Binary tree node has left and right child pointers
*/
template <class C, typename T>
class BinaryTreeNode : public GenericNode<T>
{
protected:
    C *m_left = nullptr,
      *m_right = nullptr;
public:
    explicit BinaryTreeNode(NodeFrontEnd *api, bool visible = true) : GenericNode<T>(api, LayoutType::Line, visible) {}

    /**
     * Set left node
     * @param lnode
    */
    void setLeft(C* lnode, bool placeOffset = true)
    {
        Node::nodeSanityCheck();
        if (m_left)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_left->getInnerNode()));
        }
        m_left = lnode;
        if (lnode) {
            Node::m_api->connectNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
            if (placeOffset) {
                sf::Vector2f this_pos = this->Node::getPosition();
                Node::m_api->setNodePosition(const_cast<NodeImpl*>(m_left->getInnerNode()),
                    this_pos.x-NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_X,
                    this_pos.y+NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_Y);
            }
        }
    }

    void setLeft(C& lnode, bool placeOffset = true) {
        C* ptr_lnode = &lnode;
        setLeft(ptr_lnode, placeOffset);
    }

    /**
     * Set right node
     * @param lnode
    */
    void setRight(C* lnode, bool placeOffset = true)
    {
        Node::nodeSanityCheck();
        if (m_right)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_right->getInnerNode()));
        }
        m_right = lnode;
        if (lnode) {
            Node::m_api->connectNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
            say("placeOffset")
            if (placeOffset) {
                sf::Vector2f this_pos = this->Node::getPosition();
                Node::m_api->setNodePosition(const_cast<NodeImpl*>(m_right->getInnerNode()),
                    this_pos.x+NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_X,
                    this_pos.y+NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_Y);
            }
        }
    }

    void setRight(C& lnode, bool placeOffset = true) {
        C* ptr_lnode = &lnode;
        setRight(ptr_lnode, placeOffset);
    }

    /**
     * Get left node of derived type
     * @returns C*
    */
    C* getLeft() {
        Node::nodeSanityCheck();
        return m_left;
    };

    /**
     * Get right node of derived type
     * @returns C*
    */
    C* getRight() {
        Node::nodeSanityCheck();
        return m_right;
    };

    /**
     * Apply actions on contextual menu press
    */
    void invoke() override {
        Overlay* bt_ui = this->m_overlay.createResource();
        bt_ui->createWrapper(Container{
            sf::Vector2f{70, 44},
            sf::Vector2f{MouseCache::getInstance(
                    *Node::m_api->getWindow()
                )->gMouse.getPosition(*Node::m_api->getWindow())},
            sf::Vector2i{}});
        bt_ui->addContainer(
            Container{"setLeft", [&](){
                    this->setLeft(dynamic_cast<C*>(Node::m_api->getSelectedNode()->getObservable()), false);
                }, false,
                sf::Vector2f{70, 20}, bt_ui->getWrapper()->getPosition(), sf::Vector2i{10, 10}}
        );
        bt_ui->addContainer(
            Container{"setRight", [&](){
                    this->setRight(dynamic_cast<C*>(Node::m_api->getSelectedNode()->getObservable()), false);
                }, false,
                sf::Vector2f{70, 20}, {bt_ui->getWrapper()->getPosition().x, bt_ui->getWrapper()->getPosition().y+22}, sf::Vector2i{10, 10}}
        );
        if (m_left)
            bt_ui->addContainer(
                ///
                /// Container: removes pointer to the left node.
                ///
                Container{"removeLeft", [&](){ this->setLeft(nullptr); }, true,
                    sf::Vector2f{70, 20}, {bt_ui->getWrapper()->getPosition().x, bt_ui->getWrapper()->getPosition().y+44}, sf::Vector2i{10, 10}}
            );
        if (m_right)
            bt_ui->addContainer(
                ///
                /// Container: removes pointer to the right node.
                ///
                Container{"removeRight", [&](){ this->setRight(nullptr); }, true,
                    sf::Vector2f{70, 20}, {bt_ui->getWrapper()->getPosition().x, bt_ui->getWrapper()->getPosition().y+(m_left ? 66 : 44)}, sf::Vector2i{10, 10}}
            );
        Node::m_api->mergeOverlay(*bt_ui);
    }
};

};

#endif // SRC_API_BINARYTREENODE_HPP_INCLUDED

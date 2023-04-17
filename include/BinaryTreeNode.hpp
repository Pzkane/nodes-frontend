#ifndef SRC_API_BINARYTREENODE_HPP_INCLUDED
#define SRC_API_BINARYTREENODE_HPP_INCLUDED

#include "GenericAPINode.hpp"

namespace nf {
/**
 * @brief Represents single node of a binary tree
*/
template <class C, typename T>
class BinaryTreeNode : public GenericAPINode<C,T>
{
    BinaryTreeNode *m_left = nullptr,
                   *m_right = nullptr;
protected:
    C *m_left_derived = nullptr,
      *m_right_derived = nullptr;
public:
    explicit BinaryTreeNode(NodeFrontEnd *api, bool visible = true) : GenericAPINode<C,T>(api, NodeType::List, visible) {}

    /**
     * Set left node
     * @param lnode
    */
    void setLeft(C* lnode)
    {
        Node::nodeSanityCheck();
        if (m_left)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_left->getInnerNode()));
        }
        Node::m_api->connectNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
        m_left = lnode;
        sf::Vector2f this_pos = this->Node::getPosition();
        Node::m_api->setNodePosition(const_cast<NodeImpl*>(m_left->getInnerNode()),
            this_pos.x-NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_X,
            this_pos.y+NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_Y);
        m_left_derived = lnode;
    }

    void setLeft(C& lnode) {
        C* ptr_lnode = &lnode;
        setLeft(ptr_lnode);
    }

    /**
     * Set right node
     * @param lnode
    */
    void setRight(C* lnode)
    {
        Node::nodeSanityCheck();
        if (m_right)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_right->getInnerNode()));
        }
        Node::m_api->connectNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
        m_right = lnode;
        sf::Vector2f this_pos = this->Node::getPosition();
        Node::m_api->setNodePosition(const_cast<NodeImpl*>(m_right->getInnerNode()),
            this_pos.x+NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_X,
            this_pos.y+NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_Y);
        m_right_derived = lnode;
    }

    void setRight(C& lnode) {
        C* ptr_lnode = &lnode;
        setLeft(ptr_lnode);
    }

    /**
     * Get left node of derived type
     * @returns C*
    */
    C* getLeft() {
        Node::nodeSanityCheck();
        return m_left_derived;
    };

    /**
     * Get right node of derived type
     * @returns C*
    */
    C* getRight() {
        Node::nodeSanityCheck();
        return m_right_derived;
    };
};

};

#endif // SRC_API_BINARYTREENODE_HPP_INCLUDED

#ifndef SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED
#define SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED

#include "custom_type_traits.hpp"
#include "GenericAPINode.hpp"

namespace nf {
/**
 * @brief Represents single node of a singly linked list
*/
template <class C, typename T>
class LinkedListNode : public GenericAPINode<C,T>
{
    LinkedListNode *m_next = nullptr;
protected:
    C *m_next_derived = nullptr;
public:
    explicit LinkedListNode(NodeFrontEnd *api, bool visible = true) : GenericAPINode<C,T>(api, NodeType::List, visible) {}

    /**
     * Set next node
     * @param lnode
    */
    void setNext(C* lnode)
    {
        Node::nodeSanityCheck();
        if (m_next)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_next->getInnerNode()));
        }
        Node::m_api->connectOrientedNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
        m_next = lnode;
        m_next_derived = lnode;
    }

    void setNext(C& lnode) {
        C* ptr_lnode = &lnode;
        setNext(ptr_lnode);
    }

    /**
     * Get next node of derived type
     * @returns C*
    */
    C* getNext() {
        Node::nodeSanityCheck();
        return m_next_derived;
    };
};

};

#endif // SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED

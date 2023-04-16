#ifndef SRC_API_DOUBLELISNKEDLISTNODEIMPL_HPP_INCLUDED
#define SRC_API_DOUBLELISNKEDLISTNODEIMPL_HPP_INCLUDED

#include "LinkedListNode.hpp"

namespace nf {
/**
 * @brief Represents single node of a double linked list
*/
template <class C, typename T>
class DoubleLinkedListNode : public LinkedListNode<C,T> {
    DoubleLinkedListNode *m_next = nullptr, *m_prev = nullptr;
    C *m_prev_derived = nullptr;
public:
    explicit DoubleLinkedListNode(NodeFrontEnd *api, bool visible = true) : LinkedListNode<C,T>(api, visible) {}
    ~DoubleLinkedListNode() = default;

    void setPrevious(C* lnode)
    {
        Node::nodeSanityCheck();
        if (m_prev)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_prev->getInnerNode()));
        }
        Node::m_api->connectOrientedNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
        m_prev = lnode;
        m_prev_derived = lnode;
    }

    void setPrevious(C& lnode) {
        C* ptr_lnode = &lnode;
        setPrevious(ptr_lnode);
    }

    void setPrev(C* lnode) {
        setPrevious(lnode);
    }

    void setPrev(C& lnode) {
        setPrevious(lnode);
    }

    /**
     * Get previous node of derived type
     * @returns C*
    */
    C* getPrevious() {
        Node::nodeSanityCheck();
        return m_prev_derived;
    };
};

};

#endif // SRC_API_DOUBLELISNKEDLISTNODEIMPL_HPP_INCLUDED

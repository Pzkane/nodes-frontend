#ifndef SRC_API_DOUBLYLISNKEDLISTNODEIMPL_HPP_INCLUDED
#define SRC_API_DOUBLYLISNKEDLISTNODEIMPL_HPP_INCLUDED

#include "LinkedListNode.hpp"

namespace nf {
/**
 * @brief Represents single node of a doubly linked list
*/
template <class C, typename T>
class DoublyLinkedListNode : public LinkedListNode<C,T> {
    C *m_next = nullptr, *m_prev = nullptr;
public:
    explicit DoublyLinkedListNode(NodeFrontEnd *api, bool visible = true) : LinkedListNode<C,T>(api, visible) {}

    /**
     * Set previous node
     * @param lnode
    */
    void setPrevious(C* lnode)
    {
        Node::nodeSanityCheck();
        if (m_prev)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_prev->getInnerNode()));
        }
        if (lnode)
            Node::m_api->connectOrientedNodes(Node::m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
        m_prev = lnode;
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
        return m_prev;
    };

    void invoke() override {
        LinkedListNode<C,T>::invoke();
        Overlay* dll_ui = this->m_overlay[0];
        dll_ui->addContainer(
            Container{"setPrev", [&](){
                    this->setPrev(dynamic_cast<C*>(Node::m_api->getSelectedNode()->getObservable()));
                }, false,
                sf::Vector2f{70, 20}, {dll_ui->getWrapper()->getPosition().x, dll_ui->getWrapper()->getPosition().y+(this->m_next ? 44 : 22)}, sf::Vector2i{10, 10}}
        );
        if (m_prev)
            dll_ui->addContainer(
                ///
                /// Container: removes pointer to the previous node.
                ///
                Container{"removePrev", [&](){ this->setPrev(nullptr); }, true,
                    sf::Vector2f{70, 20}, {dll_ui->getWrapper()->getPosition().x, dll_ui->getWrapper()->getPosition().y+(this->m_next ? 66 : 44)}, sf::Vector2i{10, 10}}
            );
    }
};

};

#endif // SRC_API_DOUBLYLISNKEDLISTNODEIMPL_HPP_INCLUDED

#ifndef SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED
#define SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED

#include "custom_type_traits.hpp"
#include "GenericAPINode.hpp"
#include "Overlay.hpp"
#include "MouseCache.hpp"
#include "Resource.hpp"

namespace nf {
/**
 * @brief Represents single node of a singly linked list
*/
template <class C, typename T>
class LinkedListNode : public GenericAPINode<C,T>
{
    LinkedListNode *m_next = nullptr;
    Resource<Overlay> m_overlay_pool;
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
        if (lnode == this) return;
        if (m_next)
        {
            Node::m_api->disconnectNodes(Node::m_node, const_cast<NodeImpl*>(m_next->getInnerNode()));
        }
        if (lnode != nullptr)
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

    void invoke() override {
        Overlay* ll_ui = m_overlay_pool.createResource();
        ll_ui->createWrapper(Container{
            sf::Vector2f{70, 44},
            sf::Vector2f{MouseCache::getInstance(
                    *Node::m_api->getWindow()
                )->gMouse.getPosition(*Node::m_api->getWindow())},
            sf::Vector2i{}});
        ll_ui->addContainer(
            ///
            /// Container: takes last highlighted Linked List node and performs
            ///     setNext(C*) on it.
            ///
            Container{"setNext", [&](void*){
                    // Cast order: from `void*` to -> from `Observable*` to  -> C*
                    //                                           ^
                    //                                           |
                    //                                          ~~~
                    // (to retrieve type of a value under the pointer to allow proper cast up)
                    this->setNext(
                        *dynamic_cast<C*>(
                            reinterpret_cast<Observable*>(
                                ActionObserver::getInstance()->getCallbackParameter())));
                    return nullptr;
                }, false,
                sf::Vector2f{70, 20}, ll_ui->getWrapper()->getPosition(), sf::Vector2i{10, 10}}
        );
        if (m_next_derived)
            ll_ui->addContainer(
                ///
                /// Container: removes pointer to the next node.
                ///
                Container{"removeNext", [&](void*){ this->setNext(nullptr); return nullptr; }, true,
                sf::Vector2f{70, 20}, {ll_ui->getWrapper()->getPosition().x, ll_ui->getWrapper()->getPosition().y+22}, sf::Vector2i{10, 10}}
            );
        Node::m_api->mergeOverlay(*ll_ui);
    }
};

};

#endif // SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED

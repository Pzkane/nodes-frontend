#ifndef SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED
#define SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED

#include "custom_type_traits.hpp"
#include "Node.hpp"

namespace nf {
/**
 * @brief Represents single node of a singly linked list
*/
template <class C, typename T>
class LinkedListNode : public Node
{
    LinkedListNode *m_next = nullptr;
    C *m_next_derived = nullptr;
    T m_data;
public:
    explicit LinkedListNode(NodeFrontEnd *api, bool visible = true) : Node(api, visible) {}
    ~LinkedListNode() {
        if (!m_destroyed) {
            destroy();
        }
    }

    /**
     * On-screen character representation for node's contents
     * @returns std::string
    */
    virtual std::string representation() {
        nodeSanityCheck();
        return std::string();
    };

    void setNext(C* lnode)
    {
        nodeSanityCheck();
        if (m_next)
        {
            m_api->disconnectNodes(m_node, const_cast<NodeImpl*>(m_next->getInnerNode()));
        }
        m_api->connectOrientedNodes(m_node, const_cast<NodeImpl*>(lnode->getInnerNode()));
        m_next = lnode;
        m_next_derived = lnode;
    }

    void setNext(C& lnode) {
        C* ptr_lnode = &lnode;
        setNext(ptr_lnode);
    }

    /**
     * Set/replace internal `data` element and its representation (custom type)
     * @param data of custom type T
    */
    void setData(T data)
    {
        nodeSanityCheck();
        m_data = data;
        m_node->setText(representation());
    }

    /**
     * Set/replace internal `data` element and its representation (std::string)
     * @param data of string type T
    */
    template <typename sT>
    typename std::enable_if<is_string<sT>::value>::type
    setData(sT data)
    {
        nodeSanityCheck();
        m_data = data;
        m_node->setText(std::string(data));
    }

    /**
     * Set/replace internal `data` element and its representation (any numeric type)
     * @param data of numeric type T
    */
    template <typename aT>
    typename std::enable_if<std::is_arithmetic<aT>::value>::type
    setData(aT data)
    {
        nodeSanityCheck();
        m_data = data;
        m_node->setText(std::to_string(data));
    }

    /**
     * `data` member accessor
     * @returns const T&
    */
    const T& getData() {
        nodeSanityCheck();
        return m_data;
    }

    /**
     * Get next node of derived type
     * @returns C*
    */
    C* getNext() {
        nodeSanityCheck();
        return m_next_derived;
    };
};

};

#endif // SRC_API_LISNKEDLISTNODEIMPL_HPP_INCLUDED

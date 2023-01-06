#ifndef SRC_API_LISNKEDLISTNODE_HPP_INCLUDED
#define SRC_API_LISNKEDLISTNODE_HPP_INCLUDED

#include "custom_type_traits.hpp"
#include "Node.hpp"

namespace nf {

template <typename T>
class LinkedListNode : public Node
{
    LinkedListNode *m_next = nullptr;
    T m_data;
public:
    LinkedListNode(NodeFrontEnd *api) : Node(api) {}
    ~LinkedListNode() = default;

    virtual std::string representation() { return std::string(); };

    void setNext(LinkedListNode &lnode)
    {
        if (m_next)
        {
            m_api->disconnectNodes(m_node, const_cast<_Node*>(m_next->getInnerNode()));
        }
        m_api->connectNodes(m_node, const_cast<_Node*>(lnode.getInnerNode()));
        m_next = &lnode;
    }

    void setData(T data)
    {
        m_data = data;
        m_node->setText(representation());
    }

    template <typename sT>
    typename std::enable_if<is_string<sT>::value>::type
    setData(sT data)
    {
        m_data = data;
        m_node->setText(std::string(data));
    }

    template <typename aT>
    typename std::enable_if<std::is_arithmetic<aT>::value>::type
    setData(aT data)
    {
        m_data = data;
        m_node->setText(std::to_string(data));
    }

    const T& getData() { return m_data; }
};

};

#endif // SRC_API_LISNKEDLISTNODE_HPP_INCLUDED

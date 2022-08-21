#ifndef SRC_API_LISNKEDLISTNODE_HPP_INCLUDED
#define SRC_API_LISNKEDLISTNODE_HPP_INCLUDED

#include "Node.hpp"

namespace nf {

class LinkedListNode : public Node
{
    LinkedListNode *m_next = nullptr;
public:
    LinkedListNode(NodeFrontEnd &api) : Node(api) {}
    ~LinkedListNode() = default;
    void setNext(LinkedListNode *lnode);
};

};

#endif // SRC_API_LISNKEDLISTNODE_HPP_INCLUDED

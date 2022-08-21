#include "LinkedListNode.hpp"

using namespace nf;

void LinkedListNode::setNext(LinkedListNode *lnode)
{
    if (m_next)
    {
        m_api->disconnectNodes(m_node, const_cast<_Node*>(m_next->getInnerNode()));
    }
    m_api->connectNodes(m_node, const_cast<_Node*>(lnode->getInnerNode()));
    m_next = lnode;
}

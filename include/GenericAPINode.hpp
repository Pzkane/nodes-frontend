#ifndef SRC_API_GENERICAPINODE_HPP_INCLUDED
#define SRC_API_GENERICAPINODE_HPP_INCLUDED

#include "custom_type_traits.hpp"
#include "Node.hpp"
#include "Observable.hpp"

namespace nf {
/**
 * @brief Wrapper around concrete wrapper `Node` for all API nodes
*/
template <class C, typename T>
class GenericAPINode : public Node, public Observable
{
    T m_data;
public:
    explicit GenericAPINode(NodeFrontEnd *api, NodeType type = NodeType::Generic, bool visible = true) : Node(api, this, type, visible) {}
    virtual ~GenericAPINode() {
        if (!m_destroyed) {
            destroy();
        }
    }

    /**
     * On-screen character representation for node's contents
     * Do not call directly, use `getRepresentation` to ensure node is validated
     * @returns std::string
    */
    virtual std::string representation() {
        return std::string();
    };

    /**
     * Get string representation of data
     * @returns std::string
    */
    std::string getRepresentation() {
        nodeSanityCheck();
        return representation();
    };

    /**
     * Set/replace internal `data` element and its representation (custom type)
     * @param data of custom type T
    */
    void setData(T data)
    {
        nodeSanityCheck();
        m_data = data;
        m_node->setText(getRepresentation());
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
};

};

#endif // SRC_API_GENERICAPINODE_HPP_INCLUDED

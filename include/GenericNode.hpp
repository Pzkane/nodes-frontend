#ifndef SRC_API_GENERICAPINODE_HPP_INCLUDED
#define SRC_API_GENERICAPINODE_HPP_INCLUDED

#include "custom_type_traits.hpp"
#include "Node.hpp"
#include "Observable.hpp"
#include "Resource.hpp"

namespace nf {
/**
 * @brief Wrapper around concrete wrapper `Node` for all API nodes
*/
template <typename T>
class GenericNode : public Node, public Observable
{
    T m_data;
protected:
    /// @brief Real overlay locations in memory
    Resource<Overlay> m_overlay;
public:
    explicit GenericNode(NodeFrontEnd *api, LayoutType type = LayoutType::None, bool visible = true) : Node(api, this, type, visible) {}
    /// All UI elements are managed by scene so no need to push on vector or free memory
    virtual ~GenericNode() {
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

    /**
     * @brief Highlight node on press
     * Override from Observable
    */
    void registerEntity() override {
        select();
    }
};

};

#endif // SRC_API_GENERICAPINODE_HPP_INCLUDED

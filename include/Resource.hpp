#ifndef SRC_PROPERTIES_RESOURCE_HPP_INCLUDED
#define SRC_PROPERTIES_RESOURCE_HPP_INCLUDED

#include <vector>
#include <utility>
#include <type_traits>

namespace nf {

/**
 * @brief Describes object as a resource for dynamic memory management.
 * 
 * Resource object has its own data pool to register/free data to/from.
 *
 * In context of NF, resource is used to create heap-allocated data pool to
 * be able to check and invalidate pointers to the Resource elements (which
 * also are Resources) in multiple places of a program.
*/
template<typename T>
class Resource : public std::vector<T*>
{
public:
    /**
     * Create new heap data inplace from temporary into object's pool
     *   or store it as in element
    */
    T* createResource(bool emplace = false) {
        T* data = new T;
        if (emplace || this->size() == 0)
            this->push_back(data);
        else if (this->size() > 0)
            this->operator[](0) = data;
        return data;
    }
    /**
     * Free all allocated resources and invalidates all pointers + underlying resource
     *   if it's a pointer
    */
    virtual void freeAll() {
        for (auto resource = this->begin(); resource != this->end(); ++resource) {
            // if (std::is_pointer_v<decltype(*resource)>)
                // delete **resource;
            delete *resource;
            *resource = nullptr;
        }
        this->clear();
    }
};

}; // namespace nf

#endif // SRC_PROPERTIES_RESOURCE_HPP_INCLUDED

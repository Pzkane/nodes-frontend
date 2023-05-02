#ifndef SRC_PROPERTIES_RESOURCE_HPP_INCLUDED
#define SRC_PROPERTIES_RESOURCE_HPP_INCLUDED

#include <vector>
#include <utility>

namespace nf {

/**
 * @brief Describes object as a resource for dynamic memory management.
 * 
 * Resource object has its own data pool to register/free data to/from.
*/
template<typename T>
class Resource : public std::vector<T*>
{
public:
    /**
     * Create new heap data inplace from temporary into object's pool
    */
    T* createResource() {
        T* data = new T;
        this->push_back(data);
        return data;
    }
    /**
     * Free all allocated resources and invalidates all pointers
    */
    virtual void freeAll() {
        for (auto resource = this->begin(); resource != this->end(); ++resource) {
            delete *resource;
            *resource = nullptr;
        }
        this->clear();
    }
};

}; // namespace nf

#endif // SRC_PROPERTIES_RESOURCE_HPP_INCLUDED

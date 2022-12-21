#ifndef TYPE_TRAITS_HPP_INCLUDED
#define TYPE_TRAITS_HPP_INCLUDED

#include <string>

namespace nf {

template <typename T>
struct is_string {
    static const bool value = false;
};

template <>
struct is_string<std::string> {
    static const bool value = true;
};

template <>
struct is_string<const char*> {
    static const bool value = true;
};

}; // namespace nf

#endif // TYPE_TRAITS_HPP_INCLUDED
#ifndef SRC_HELPERS_EVENTTYPES_HPP_INCLUDED
#define SRC_HELPERS_EVENTTYPES_HPP_INCLUDED

#include <SFML/Window.hpp>

namespace nf {

enum class EventType
{
    addNode,
    addEdge,
    addOEdge,
    addWEdge,
    addWOEdge,
    addOverlay,
    disconnectNodes,
    destroyNode
};

};

#endif // SRC_HELPERS_EVENTTYPES_HPP_INCLUDED
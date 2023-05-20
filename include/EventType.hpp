#ifndef SRC_HELPERS_EVENTTYPES_HPP_INCLUDED
#define SRC_HELPERS_EVENTTYPES_HPP_INCLUDED

#include <SFML/Window.hpp>

namespace nf {

/**
 * Enum for MainScene update by input
*/
enum class EventType
{
    addNode,
    addEdge,
    addOEdge,
    addWEdge,
    addWOEdge,
    addOverlay,
    disconnectNodes,
    destroyNode,
    queryEdge
};

};

#endif // SRC_HELPERS_EVENTTYPES_HPP_INCLUDED
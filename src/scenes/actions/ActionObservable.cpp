#include "ActionObservable.hpp"

using namespace nf;

void ActionObservable::execute() {
    struct Observable_Ptr_Not_Set{};
    if (!m_entity) throw Observable_Ptr_Not_Set{};
    m_entity->invoke();
}
#include "ActionObservable.hpp"

using namespace nf;

struct Observable_Ptr_Not_Set{};

void ActionObservable::execute() {
    if (!m_entity) throw Observable_Ptr_Not_Set{};
    m_entity->invoke();
}

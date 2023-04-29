#ifndef SRC_HELPERS_SAFEQUEUE_HPP_INCLUDED
#define SRC_HELPERS_SAFEQUEUE_HPP_INCLUDED

#include <queue>
#include <mutex>

namespace nf {

namespace Utils
{
/**
 * @brief Thread-safe locking queue 
*/
template <typename Tq>
class SafeQueue
{
    using _lg = std::lock_guard<std::mutex>;
    std::queue<Tq> q;
    std::mutex mt;

public:
    SafeQueue() {}
    ~SafeQueue() = default;
    void push(const Tq &el);
    void pop();
    Tq &front();
    size_t size();
    bool empty();
};

template <typename Tq>
void SafeQueue<Tq>::push(const Tq &el)
{
    _lg lock(mt);
    q.push(el);
}

template <typename Tq>
void SafeQueue<Tq>::pop()
{
    _lg lock(mt);
    q.pop();
}

template <typename Tq>
Tq &SafeQueue<Tq>::front()
{
    _lg lock(mt);
    return q.front();
}

template <typename Tq>
size_t SafeQueue<Tq>::size()
{
    _lg lock(mt);
    return q.size();
}

template <typename Tq>
bool SafeQueue<Tq>::empty()
{
    _lg lock(mt);
    return q.empty();
}

}; // namespace Utils

}; // namespace nf

#endif // SRC_HELPERS_SAFEQUEUE_HPP_INCLUDED

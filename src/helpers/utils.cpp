#include "utils.hpp"

template <typename T>
T get_random_number(T from, T to)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(from, to);

    return dist(rng);
}

template int get_random_number<int>(int from, int to);
template float get_random_number<float>(float from, float to);

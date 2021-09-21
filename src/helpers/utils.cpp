#include "utils.hpp"

template <typename T>
T Utils::get_random_number(T from, T to)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(from, to);

    return dist(rng);
}

template int Utils::get_random_number<int>(int, int);
template float Utils::get_random_number<float>(float, float);

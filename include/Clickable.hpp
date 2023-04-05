#ifndef PROPERTIES_CLICKABLE_HPP_INCLUDED
#define PROPERTIES_CLICKABLE_HPP_INCLUDED

#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Callbacks.hpp"

namespace nf {

/**
 * !Not finished
 * @brief Describes clickable property of an object with mouse interaction
 * Used mainly for custom callbacks
*/
template<typename Tc>
class Clickable
{
    bool m_successDrag = false;
    sf::Vector2f m_offsetMousePos;
    size_t click_delay_ms_;
    Tc callback_;

    const std::chrono::time_point<std::chrono::high_resolution_clock> null_timestamp_{}; // 1970-01-01
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

public:
    Clickable() { init(); }
    Clickable(size_t ms) : click_delay_ms_(ms) { init(); }
    void init()
    {
        callback_ = nullptr;
    }
    virtual ~Clickable() = default;
    /**
     * Set delay interval for process to consider it as double click
     * @param ms Delay in milliseconds
    */
    void setDelayForDBLClick(size_t ms)
    {
        click_delay_ms_ = ms;
    }
    /**
     * Set callback invoked on double click
     * @param callback Callback function pointer
    */
    void setCallback(VoidCallback callback)
    {
        callback_ = callback;
    }
    /**
     * Invoke previously set callback
    */
    void invokeCallback()
    {
        if (!callback_) return;
        //TODO: implement DBL click
        /*if (start_time_ == null_timestamp_)
        {
            start_time_ = std::chrono::high_resolution_clock::now();
        } else 
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            double elapsed = std::chrono::duration<double, std::milli>(end - start_time_).count();
            if (elapsed <= click_delay_ms_)
            {
                start_time_ = null_timestamp_;
                callback_();
            }
        }*/
        callback_();
    }
};

};

#endif // PROPERTIES_CLICKABLE_HPP_INCLUDED

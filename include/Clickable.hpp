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
    size_t m_click_delay_ms;
    Tc m_callback_lmb, m_callback_rmb, m_callback_mmb;

    const std::chrono::time_point<std::chrono::high_resolution_clock> m_null_timestamp{}; // 1970-01-01
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;

public:
    Clickable() { init(); }
    Clickable(size_t ms) : m_click_delay_ms(ms) { init(); }
    void init()
    {
        m_callback_lmb = m_callback_rmb = m_callback_mmb = nullptr;
    }
    virtual ~Clickable() = default;
    /**
     * Set delay interval for process to consider it as double click
     * @param ms Delay in milliseconds
    */
    void setDelayForDBLClick(size_t ms)
    {
        m_click_delay_ms = ms;
    }
    /**
     * Set callback invoked on LMB click
     * @param callback Callback function pointer
    */
    void setLMBCallback(VoidCallback callback)
    {
        m_callback_lmb = callback;
    }
    /**
     * Set callback invoked on RMB click
     * @param callback Callback function pointer
    */
    void setRMBCallback(VoidCallback callback)
    {
        m_callback_rmb = callback;
    }
    /**
     * Set callback invoked on MMB click
     * @param callback Callback function pointer
    */
    void setMMBCallback(VoidCallback callback)
    {
        m_callback_mmb = callback;
    }
    /**
     * Invoke previously set LMB callback
    */
    void invokeLMBCallback()
    {
        if (!m_callback_lmb) return;
        //TODO: implement DBL click
        /*if (m_start_time == m_null_timestamp)
        {
            m_start_time = std::chrono::high_resolution_clock::now();
        } else 
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            double elapsed = std::chrono::duration<double, std::milli>(end - m_start_time).count();
            if (elapsed <= m_click_delay_ms)
            {
                m_start_time = m_null_timestamp;
                m_callback();
            }
        }*/
        m_callback_lmb();
    }
    /**
     * Invoke previously set RMB callback
    */
    void invokeRMBCallback() {
        if (!m_callback_rmb) return;
        m_callback_rmb();
    }
    /**
     * Invoke previously set MMB callback
    */
    void invokeMMBCallback() {
        if (!m_callback_mmb) return;
        m_callback_mmb();
    }
};

};

#endif // PROPERTIES_CLICKABLE_HPP_INCLUDED

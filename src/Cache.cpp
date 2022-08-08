#include "Cache.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"

#define log_err_type(type) { say("ERROR: Couldn't load " + std::string(type) + " cursor!"); }

using namespace nf;

static FontFlags ff;

std::vector<sf::Cursor*> Cache::m_cursors;

static const size_t CURSOR_TYPE_COUNT = 2;

void Cache::_initCursors()
{
    for (size_t i = 0; i < CURSOR_TYPE_COUNT; ++i)
    {
        sf::Cursor *c;
        switch (i)
        {
        case CursorType::Arrow:
            c = new sf::Cursor;
            if (c->loadFromSystem(sf::Cursor::Arrow))
                m_cursors.push_back(c);
            else
                log_err_type("Arrow");
            break;

        case CursorType::Hand:
            c = new sf::Cursor;
            if (c->loadFromSystem(sf::Cursor::Hand))
                m_cursors.push_back(c);
            else
                log_err_type("Hand");
            break;

        default:
            throw std::runtime_error("ERROR: Cursor type iteration unspecified!");
            break;
        }
    }
}

Cache::Cache()
{
    _initCursors();
}

#ifndef SRC_SHAPES_GL_TRIANGLE_HPP_INCLUDED
#define SRC_SHAPES_GL_TRIANGLE_HPP_INCLUDED

#include <SFML/OpenGL.hpp>

namespace nf {

class GL_Triangle
{
public:
    GL_Triangle() {}
    ~GL_Triangle() = default;
    void draw();
};

};

#endif // SRC_SHAPES_GL_TRIANGLE_HPP_INCLUDED

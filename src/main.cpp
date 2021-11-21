#include <thread>
#include "NodeFrontEnd.hpp"

int main()
{

    NodeFrontEnd api;
    api.setWindowColor(sf::Color(219, 189, 189));
    for (int i = 0; i < 10; ++i)
    {
        Node *node = api.addNode("test text");
        node->setPosition(i, i);
    }
    api.launch();

    return 0;
}
